#ifndef __MODULELSTAGECOMPLETED_H__
#define __MODULESTAGECOMPLETED_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;

class ModuleStageCompleted : public Module
{
public:
	ModuleStageCompleted();
	~ModuleStageCompleted();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	
	Mix_Music* music_stage_cleared = nullptr;
	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	bool fading = false;

	float foreground_pos;
	bool forward;
};

#endif // __MODULESTAGECOMPLETED_H__