#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleLevel2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleIntro.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleStageCompleted.h"

#include <stdio.h>

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
	App->level1->Disable();
	App->level2->Disable();
	App->intro->Disable();
	


	App->render->camera.x = 0;
	App->render->camera.y = 0;

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
	App->audio->Disable();
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleStageCompleted::Update()
{

	sprintf_s(App->player->score_text, 10, "%7d", App->player->score);
	sprintf_s(App->player->high_score_text, 10, "%7d", App->player->high_score);

	App->fonts->BlitText(0, 1, App->player->red_font_score, App->player->user_interface);
	App->fonts->BlitText(0, 9, App->player->yellow_font_score, App->player->score_text);
	App->fonts->BlitText(88, 9, App->player->yellow_font_score, App->player->high_score_text);

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background);



	if (App->input->keyboard[SDL_SCANCODE_TAB] && App->fade->IsFading()==false) {

		App->fade->FadeToBlack(this, App->level2);		

	}

	return UPDATE_CONTINUE;
}