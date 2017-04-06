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
#include "ModuleStageCompleted.h"



ModuleStageCompleted::ModuleStageCompleted()
{

	background.x = 0;
	background.y = 0;
	background.w = 224;
	background.h = 256;

}

ModuleStageCompleted::~ModuleStageCompleted()
{}

// Load assets
bool ModuleStageCompleted::Start()
{
	App->audio->Enable();

	LOG("Loading level 1");

	music_stage_cleared = App->audio->Load_Music("Assets/Audio/StageCompleted.ogg");
	if (!music_stage_cleared) {
		LOG("Error loading lvl1 music: %s", Mix_GetError)
	}
	App->audio->Play_Music(music_stage_cleared);

	graphics = App->textures->Load("Assets/Images/End_Stage_01.png");

	return true;
}

// UnLoad assets
bool ModuleStageCompleted::CleanUp()
{
	LOG("Unloading Stage Cleared");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleStageCompleted::Update()
{

	

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.0f);


	if (App->input->keyboard[SDL_SCANCODE_TAB] && fading == false) {

		App->fade->FadeToBlack(this, App->level2);
		fading = true;

	}

	return UPDATE_CONTINUE;
}