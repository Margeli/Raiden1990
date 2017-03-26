#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#define SHIP_MAX 3
#define SHIP_MIN 0
//int counter_ship_movement=0;
struct SDL_Texture;

class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();

	bool Start();
	update_status Update();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;	
	Animation flag;
	SDL_Rect ship;
	Animation girl;
};

#endif