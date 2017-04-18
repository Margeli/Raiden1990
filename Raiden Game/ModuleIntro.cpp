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
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModulePlayer2.h"



ModuleIntro::ModuleIntro()
{
	background.x = 0;
	background.y = 0;
	background.w = 223;
	background.h = 256;


}

ModuleIntro::~ModuleIntro()
{

}

// Load assets
bool ModuleIntro::Start()
{
	LOG("Loading Intro screen");

	graphics = App->textures->Load("Assets/Images/Intro_Raiden.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	App->particles->Disable();
	App->audio->Enable(); 
	App->player->Disable();
	App->collision->Disable();
	App->enemies->Disable();


	return true;
}


// UnLoad assets
bool ModuleIntro::CleanUp()
{
	LOG("Unloading intro screen");

	App->textures->Unload(graphics);
	App->audio->Disable();
	

	return true;
}

// Update: draw background
update_status ModuleIntro::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background); 

	if (App->input->keyboard[SDL_SCANCODE_1]) {
		
		App->player2->player2;
	}
	else if (App->input->keyboard[SDL_SCANCODE_2]) {
		
		App->player2->player2 = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_TAB] && App->fade->IsFading() == false) {

		App->fade->FadeToBlack(this, App->level1);
		

	}

	return UPDATE_CONTINUE;
}