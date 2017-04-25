#ifndef __MODULEINTRO_H__
#define __MODULEINTRO_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleIntro : public Module
{
public:
	ModuleIntro();
	~ModuleIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	bool fading = false;

	bool forward;

	char *user_interface;
	int red_font_score = 0;
	int yellow_font_score = 0;
};

#endif // __MODULELINTRO_H__
