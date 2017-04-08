#ifndef __MODULEAUDIO_H__
#define __MODULEAUDIO_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"



class ModuleAudio : public Module
{
public:
	ModuleAudio();
	virtual ~ModuleAudio();

	bool Init();
	

	Mix_Music* music = nullptr;
	Mix_Chunk* fx_shoot = nullptr;


	Mix_Music*Load_Music(const char* path);
	Mix_Chunk* Load_Fx(const char* path); 

	void Play_Music(Mix_Music*musi);
	void Play_Fx(Mix_Chunk* Chun);

	void Unload_Fx(Mix_Chunk *uchunk);
	void Unload_Music(Mix_Music *umusic);
		

	update_status Update();
	bool CleanUp();
	bool Close();
	

	bool playing = false;
};





#endif // __MODULEAUDIO_H__
