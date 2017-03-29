#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer()
{
	spaceship.x = 80;
	spaceship.y = 13;
	spaceship.w = 24;
	spaceship.h = 27 ;
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Images/Raiden_Spaceship.png"); // arcade version
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
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{

		position.y += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{

		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == 1)
	{

		position.x += speed;
	}

	App->render->Blit(graphics, position.x, position.y, &spaceship, 0.75f);//-50, -2965
	
	return UPDATE_CONTINUE;
}