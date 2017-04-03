#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleLevel2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleIntro.h"


// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleLevel2::ModuleLevel2()
{
	// Background / sky
	background.x = 0;
	background.y = 0;
	background.w = 302;
	background.h = 5362;
}
ModuleLevel2::~ModuleLevel2()
{}

// Load assets
bool ModuleLevel2::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Assets/Images/lvl2_tilemap.png");

	
	App->player->Enable();

	return ret;
}

// Load assets
bool ModuleLevel2::CleanUp()
{
	
	LOG("Unloading level 2");

	App->textures->CleanUp();

	App->player->Disable();


	return true;
}

// Update: draw background
update_status ModuleLevel2::Update()
{
	// Draw everything --------------------------------------	
	
	App->render->Blit(graphics, -50,-5100 , &background, 0.75f); // back of the room
	

	if (App->input->keyboard[SDL_SCANCODE_TAB] && fading == false) {

		App->fade->FadeToBlack(this, App->intro);
		fading = true;
	}

	return UPDATE_CONTINUE;
}