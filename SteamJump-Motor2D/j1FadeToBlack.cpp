#include <math.h>
#include "j1App.h"
#include "j1FadeToBlack.h"
#include "j1Render.h"
#include "p2Defs.h"
#include "j1Window.h"
#include "p2Log.h"

#include "../SteamJump-Motor2D/SDL/include/SDL_render.h"
#include "../SteamJump-Motor2D/SDL/include/SDL_timer.h"

bool j1FadeToBlack::Awake(pugi::xml_node&) {
	name.create("fade");

	uint width, height = 0u;
	App->win->GetWindowSize(width, height);

	screen = { 0,0,(int)width * (int)App->win->GetScale(),(int)height * (int)App->win->GetScale() };
	return true;
}

j1FadeToBlack::~j1FadeToBlack()
{}

bool j1FadeToBlack::Start()
{
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

bool j1FadeToBlack::PostUpdate()
{
	bool ret = true;
	if (current_step == fade_step::none)
		return ret;

	Uint32 now = SDL_GetTicks() - start_time;
	
	if (current_step == fade_step::fade_to_black) {
		fadingPerCent = MIN(1.0F, ((float)now * 2.0F) / (float)total_time);
		if (now >= total_time * 0.5F) {

			// TODO: Change from level to leve here with all the necessary changes

			current_step = fade_step::fade_from_black;
		}
	}
	else if (current_step == fade_step::fade_from_black) {
		fadingPerCent = MAX(0.0F, 2.0F - ((float)now * 2.0F) / (float)total_time);
		if (now >= total_time) {
			current_step = fade_step::none;
			fadingPerCent = 0.0F;
		}
	}

	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(fadingPerCent * 255.0F));
	SDL_RenderFillRect(App->render->renderer, &screen);

	return ret;
}

bool j1FadeToBlack::FadeToBlack(const char* lvlname, float time)
{
	bool ret = false;

	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 1000.0F);
		
		// add the change to do while fading to black

		ret = true;
	}
	return ret;
}

bool j1FadeToBlack::IsFading() const
{
	return current_step != fade_step::none;
}