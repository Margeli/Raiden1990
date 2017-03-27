#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleLevel2.h"
#include "ModuleFadeToBlack.h"



ModuleLevel1::ModuleLevel1()
{

	// foreground
	foreground.x = 352;
	foreground.y = 134;
	foreground.w = 351;
	foreground.h = 3265;

	// Background / sky
	background.x = 0;
	background.y = 134;
	background.w = 351;
	background.h = 3265;

	
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading level 1");
	
	graphics = App->textures->Load("lvl1_tilemap.png");

	
	App->player->Enable();

	return true;
}

// UnLoad assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading level 1");

	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	
	// Draw everything --------------------------------------
	App->render->Blit(graphics, -50, -2965, &background, 0.75f); // sea and sky

	App->render->Blit(graphics, -50, -2965, &foreground, 0.75f);
	



	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false) {
	
		App->fade->FadeToBlack(App->level1, App->level2);
		fading = true;
		
	}

	return UPDATE_CONTINUE;
}