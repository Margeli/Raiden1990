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
	SDL_Texture* graphics2 = nullptr;
	Animation* current_animation = nullptr;
	Animation loading_screen;
	SDL_Rect background;

	iPoint position;

	bool fading = false;

	bool forward;
};

#endif // __MODULELINTRO_H__
