#ifndef __MODULELEVEL1_H__
#define __MODULELEVEL1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;

class ModuleLevel1 : public Module
{
public:
	ModuleLevel1();
	~ModuleLevel1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	Mix_Music* music_lvl1 = nullptr;
	SDL_Rect foreground;
	SDL_Rect background;
	bool fading = false;

	Collider* col;

	float foreground_pos;
	bool forward;
};

#endif // __MODULELEVEL1_H__