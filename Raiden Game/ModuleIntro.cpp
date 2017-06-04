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
#include "ModuleFonts.h"

#include <stdio.h>


ModuleIntro::ModuleIntro()
{
	background.x = 0;
	background.y = 0;
	background.w = 224;
	background.h = 256;
/*
	loading.PushBack({ 449,257,224,256 });
	loading.PushBack({ 225,257,224,256 });
	loading.PushBack({ 0,257,224,256 });
	loading.PushBack({ 674,0,224,256 });
	loading.PushBack({ 449,0,224,256 });
	loading.PushBack({ 225,0,224,256 });
	loading.PushBack({ 0,0,224,256 });
	loading.PushBack({ 0,0,224,256 });
	loading.PushBack({ 225,0,224,256 });
	loading.PushBack({ 449,0,224,256 });
	loading.PushBack({ 674,0,224,256 });
	loading.PushBack({ 0,257,224,256 });
	loading.PushBack({ 225,257,224,256 });
	loading.PushBack({ 449,257,224,256 });
	loading.speed = 0.3f;*/

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
	//App->collision->Disable();
	App->enemies->Disable();

	if (App->player->destroyed) { //Resets score
		App->player->score = 0;
		App->player->destroyed = false;
	}
	if (App->player2->destroyed) {
		App->player2->score = 0;
		App->player2->destroyed = false;
	}


	user_interface = "    1UP   HI-SCORE    2UP ";
	red_font_score = App->fonts->Load("Assets/Images/Font.png", "> ?@ABCDEFGHIJKLMNOPQRSTUVWXYZ!¡?_*#$%&'()x+.-,;[].{.}./0123456789:", 3);
	yellow_font_score = App->fonts->Load("Assets/Images/Font.png", "> ?@ABCDEFGHIJKLMNOPQRSTUVWXYZ!¡?_*#$%&'()x+.-,;[].{.}./0123456789:", 3);


	return true;
}


// UnLoad assets
bool ModuleIntro::CleanUp()
{
	LOG("Unloading intro screen");

	App->textures->Unload(graphics);
	
	
	App->fonts->UnLoad(red_font_score);
	App->fonts->UnLoad(yellow_font_score);
	

	return true;
}

// Update: draw background
update_status ModuleIntro::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background); 

	
	
	App->fonts->BlitText(0, 1, red_font_score, user_interface);
	
	App->fonts->BlitText(88, 9, yellow_font_score, App->player->high_score_text);

	if (App->input->keyboard[SDL_SCANCODE_1]|| App->input->gamepad[6] == KEY_STATE::KEY_REPEAT) {
		
		App->player2->player2=false;
		
		App->fade->FadeToBlack(this, App->level1);
		
	}
	else if (App->input->keyboard[SDL_SCANCODE_2]) {
		
		App->player2->player2 = true;
		
		App->fade->FadeToBlack(this, App->level1);
	}

	/*if ((( App->input->gamepad[6] == KEY_STATE::KEY_REPEAT)||(App->input->keyboard[SDL_SCANCODE_TAB])) && App->fade->IsFading() == false) {

		
		App->fade->FadeToBlack(this, App->level1);
		

	}*/

	return UPDATE_CONTINUE;
}