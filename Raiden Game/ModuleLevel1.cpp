#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleStageCompleted.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleLevel2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleIntro.h"
#include "ModuleAudio.h"



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
	App->audio->Enable();
	App->player->Enable();
	
	LOG("Loading level 1");

	music_lvl1 = App->audio->Load_Music("Assets/Audio/00_Raiden.ogg");
	if (!music_lvl1) {
	LOG("Error loading lvl1 music: %s",Mix_GetError)
	}
	App->audio->Play_Music(music_lvl1);
	
	graphics = App->textures->Load("Assets/Images/lvl1_tilemap.png");
	

	
	

	return true;
}

// UnLoad assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading level 1");

	App->textures->Unload(graphics);

	App->player->Disable();

	

	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	
	float scroll_speed = 0.5f;

	App->player->position.y += 1;
	App->render->camera.y += 2;

	// Draw everything --------------------------------------
	App->render->Blit(graphics, -50, -2965, &background, 0.75f); 

	App->render->Blit(graphics, -50, -2965, &foreground, 0.75f);
	



	if (App->input->keyboard[SDL_SCANCODE_TAB] && fading == false) {
	
		App->fade->FadeToBlack(this, App->StageCompleted);
		fading = true;
		
	}

	return UPDATE_CONTINUE;
}