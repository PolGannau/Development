#include <math.h>
#include "j1App.h"
#include "j1FadeToBlack.h"
#include "j1Render.h"
#include "j1Globals.h"
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
	float normalized = MIN(1.0F, (float)now / (float)total_time);

	switch (current_step)
	{
	case fade_step::fade_to_black:
	{
		if (now >= total_time)
		{
			to_disable->Disable();
			to_enable->Enable();
			total_time += total_time;
			start_time = SDL_GetTicks();
			current_step = fade_step::fade_from_black;
		}
	} break;

	case fade_step::fade_from_black:
	{
		normalized = 1.0F - normalized;

		if (now >= total_time)
			current_step = fade_step::none;
	} break;
	}

	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0F));
	SDL_RenderFillRect(App->render->renderer, &screen);

	return ret;
}

bool j1FadeToBlack::FadeToBlack(j1Module* module_off, j1Module* module_on, float time)
{
	bool ret = false;

	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5F * 1000.0F);
		to_enable = module_on;
		to_disable = module_off;
		ret = true;
	}
	return ret;
}

bool j1FadeToBlack::IsFading() const
{
	return current_step != fade_step::none;
}