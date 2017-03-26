#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleLevel2.h"
#include "ModuleFadeToBlack.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleLevel1::ModuleLevel1()
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// foreground
	foreground.x = 8;
	foreground.y = 24;
	foreground.w = 521;
	foreground.h = 181;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// Girl Animation
	girl.PushBack({624, 16, 32, 56});
	girl.PushBack({624, 80, 32, 56});
	girl.PushBack({624, 144, 32, 56});
	girl.speed = 0.05f;

	// for moving the foreground
	foreground_pos = 0;
	forward = true;
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading level 1");
	
	graphics = App->textures->Load("ken_stage.png");

	// TODO 1: Enable (and properly disable) the player module
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
	// Calculate boat Y position -----------------------------
	if(foreground_pos < -6.0f)
		forward = false;
	else if(foreground_pos > 0.0f)
		forward = true;
	
	if(forward)
		foreground_pos -= 0.02f;
	else
		foreground_pos += 0.02f;

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	App->render->Blit(graphics, 0, (int)foreground_pos, &foreground, 0.92f);
	App->render->Blit(graphics, 192, 104 + (int)foreground_pos, &(girl.GetCurrentFrame()), 0.92f); // girl animation
	
	App->render->Blit(graphics, 0, 170, &ground);

	// TODO 3: make so pressing SPACE the HONDA stage is loaded

	if (App->input->keyboard[SDL_SCANCODE_SPACE] && fading == false) {
	
		App->fade->FadeToBlack(App->level1, App->level2);
		fading = true;
		
	}

	return UPDATE_CONTINUE;
}