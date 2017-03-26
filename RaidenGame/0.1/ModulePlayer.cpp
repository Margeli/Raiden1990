#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer()
{
	spaceship.x = 104;
	spaceship.y = 97;
	spaceship.w = 27;
	spaceship.h = 28 ;
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Raiden_Spaceship.png"); // arcade version
	if (graphics == nullptr) {
		LOG("Error loading player textures %s", SDL_GetError);
		ret = false;
	}

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	

	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		
		position.y -= speed;
	}

	App->render->Blit(graphics, -50, -2965, &spaceship, 0.75f);
	
	return UPDATE_CONTINUE;
}