#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleLevel1.h"
#include "ModuleLevel2.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio() : Module()
{}

ModuleAudio::~ModuleAudio()
{}

bool ModuleAudio::Init()
{

	LOG("Init Mixer library");
	bool ret = true;
	int flags = MIX_INIT_OGG;

	int Mix_VolumeMusic(MIX_MAX_VOLUME/2);//<--- not working, need check to decrease volume.

	if (Mix_Init(flags) == 0)
	{
		LOG("Error initializing audio: %s", SDL_GetError())
			ret = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		LOG("Error opening Audio: %s", SDL_GetError())
			ret = false;
	}		


	return ret;

}

update_status ModuleAudio::Update()
{
	
	if ((App->audio->IsEnabled())&&(!playing)) {	
		Init();
		playing = true;
	}
	
	else if ((!App->audio->IsEnabled()) && (playing)) {	
		playing = false;
		Close();		
	}
	return UPDATE_CONTINUE;
}

bool ModuleAudio::Close()
{
	Mix_CloseAudio();
	return true;
}

bool ModuleAudio::CleanUp()
{
	LOG("Freeing audio  library");
		
	Mix_CloseAudio();	
	Mix_Quit();

	return true;
}

Mix_Music* ModuleAudio::Load_Music(const char* path)
{

	music = Mix_LoadMUS(path);
	if (music == NULL)
	{
		LOG("Error loading sound: %s", SDL_GetError())
	}

	return music;
}

Mix_Chunk*  ModuleAudio::Load_Fx(const char* path) {

	fx_shoot = Mix_LoadWAV(path);
		if (fx_shoot == NULL)
		{
			LOG("Error loading fx: %s", SDL_GetError())
		}
	return fx_shoot;
}

void ModuleAudio::Play_Music(Mix_Music*musi) {

	if (Mix_PlayMusic(musi, -1) == -1) {
		LOG("Error playing music: %s\n", Mix_GetError());

	}
}

void ModuleAudio::Play_Fx(Mix_Chunk*chun) {

	if (Mix_PlayChannel(-1, chun, 0) == -1) {
		LOG("Error reproducing fx: %s", Mix_GetError())
	}
}
		
void ModuleAudio::Unload_Fx(Mix_Chunk *uchunk) {

	Mix_FreeChunk(uchunk);

}
void ModuleAudio::Unload_Music(Mix_Music *umusic) {

	Mix_FreeMusic(umusic);	

}
