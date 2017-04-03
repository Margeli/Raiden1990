#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleLevel1.h"
#include "ModuleLevel2.h"

#include "SDL/include/SDL.h"

ModuleAudio::ModuleAudio() : Module()
{
	
}

// Destructor
ModuleAudio::~ModuleAudio()
{}

bool ModuleAudio::Init()
{

	LOG("Init Mixer library");
	bool ret = true;
	int flags = MIX_INIT_OGG;

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
	
	

	if ((Mix_PlayMusic(music, -1) == -1)&&(!first_load))
	{
		LOG("Error reproducing audio: %s", SDL_GetError())
			return false;
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
		Close();
		playing = false;
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

Mix_Music* const ModuleAudio::Load(const char* path)
{

	music = Mix_LoadMUS(path);
	if (music == NULL)
	{
		LOG("Error loading sound: %s", SDL_GetError())
	}

	return music;
}
