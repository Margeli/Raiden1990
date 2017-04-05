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



ModuleIntro::ModuleIntro()
{
	graphics2 = NULL;
	current_animation = NULL;
	position.x = 0;
	position.y = 0;
	
	
	background.x = 0;
	background.y = 0;
	background.w = 223;
	background.h = 256;

	loading_screen.PushBack({ 449, 256, 220, 255 });
	loading_screen.PushBack({ 224, 256, 220, 255 });
	loading_screen.PushBack({ 0, 256, 220, 255 });
	loading_screen.PushBack({ 674, 0, 220, 255 });
	loading_screen.PushBack({ 449, 0, 220, 255 });
	loading_screen.PushBack({ 224, 0, 220, 255 });
	loading_screen.PushBack({ 0, 0, 220, 255 });
	loading_screen.PushBack({ 224, 0, 220, 255 });
	loading_screen.PushBack({ 449, 0, 220, 255 });
	loading_screen.PushBack({ 674, 0, 220, 255 });
	loading_screen.PushBack({ 0, 256, 220, 255 });
	loading_screen.PushBack({ 224, 256, 220, 255 });
	loading_screen.PushBack({ 449, 256, 220, 255 });


}

ModuleIntro::~ModuleIntro()
{

}

// Load assets
bool ModuleIntro::Start()
{
	LOG("Loading Intro screen");

	graphics = App->textures->Load("Assets/Images/Intro_Raiden.png");
	graphics2 = App->textures->Load("Assets/Images/loading_screen.png");

	App->audio->Disable();
	App->player->Disable();

	

	return true;
}

// UnLoad assets
bool ModuleIntro::CleanUp()
{
	LOG("Unloading intro screen");

	App->textures->CleanUp();

	App->player->Disable();


	return true;
}

// Update: draw background
update_status ModuleIntro::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.0f);
	


	if (App->input->keyboard[SDL_SCANCODE_TAB] ){
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), 0.75f);
	}
	if (App->input->keyboard[SDL_SCANCODE_TAB] && fading==false){
		App->fade->FadeToBlack(this, App->level1);
		fading = true;

	}

	return UPDATE_CONTINUE;
}