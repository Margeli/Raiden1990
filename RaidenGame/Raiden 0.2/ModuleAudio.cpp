/*#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h

ModuleAudio::ModuleAudio() : Module()
{
	for (uint i = 0; i < MAX_TEXTURES; ++i)
		textures[i] = nullptr;
}

// Destructor
ModuleAudio::~ModuleAudio()
{}

// Called before render is available
bool ModuleAudio::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before q	uitting
bool ModuleAudio::CleanUp()
{
	LOG("Freeing textures and Image library");

	for (uint i = 0; i < MAX_TEXTURES; ++i)
		if (textures[i] != nullptr)
			SDL_DestroyTexture(textures[i]);

	IMG_Quit();
	return true;
}

// Load new texture from file path
SDL_Texture* const ModuleTextures::Load(const char* path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(App->render->renderer, surface);

		if (texture == NULL)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			bool room = false;
			for (int i = 0; i < MAX_TEXTURES; ++i)
			{
				if (textures[i] == nullptr)
				{
					textures[i] = texture;
					room = true;
					break;
				}
			}
			if (room == false)
				LOG("Texture buffer overflow");
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

bool ModuleTextures::Unload(SDL_Texture * texture)
{
	bool ret = false;

	if (texture != nullptr)
	{
		for (int i = 0; i < MAX_TEXTURES; ++i)
		{
			if (textures[i] == texture)
			{
				textures[i] = nullptr;
				ret = true;
				break;
			}
		}
		SDL_DestroyTexture(texture);
	}

	return ret;
}
*/