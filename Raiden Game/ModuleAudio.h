#ifndef __MODULEAUDIO_H__
#define __MODULEAUDIO_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	

	Mix_Music* music = nullptr;
	Mix_Chunk* fx_shoot = nullptr;


	Mix_Music* const Load(const char* path);

	update_status Update();
	bool CleanUp();
	bool Close();
	bool first_load=true;

	bool playing = false;
};





#endif // __MODULEAUDIO_H__
