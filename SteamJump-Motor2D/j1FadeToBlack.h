#ifndef __J1EFADETOBLACK_H__
#define __J1FADETOBLACK_H__

#include "j1Module.h"
#include "../SteamJump-Motor2D/SDL/include/SDL_rect.h"

class j1FadeToBlack : public j1Module
{
public:
	j1FadeToBlack() {};
	~j1FadeToBlack();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PostUpdate();
	bool FadeToBlack(const char* lvlname, float time = 1.0F);
	bool IsFading() const;

private:

	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	}current_step = fade_step::none;

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;
	float fadingPerCent = 0.0F;
	p2SString lvlToLoad;
};

#endif // !__J1FADETOBLACK_H__
