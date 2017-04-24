#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleStageCompleted.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleLevel2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleIntro.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModulePowerUps.h"



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
	if (App->player2->player2 == true)
		App->player2->Enable();
	else if (App->player2->player2)
		App->player2->Disable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	if (App->player2->player2 == false) {

		App->player->position.x = 111; //position if there's only 1 player
		App->player->position.y = 150;
	}
	else {

		App->player->position.x = 71; //position if there are 2 players
		App->player->position.y = 150;
	}
	if ((!App->player->godmode)&&(!first)){
		App->player->spaceship_collider = App->collision->AddCollider({ 0,0, 23, 26 }, COLLIDER_PLAYER, App->player);
	App->player->spaceship_collider->SetPos(App->player->position.x, App->player->position.y);
}

	

	
	
	LOG("Loading level 1");

	//music_lvl1 = App->audio->Load_Music("Assets/Audio/00_Raiden.ogg");// UNCOMMENT FOR PLAYING MUSIC
	if (!music_lvl1) {
	LOG("Error loading lvl1 music: %s",Mix_GetError)
	}
	App->audio->Play_Music(music_lvl1);
	
	graphics = App->textures->Load("Assets/Images/lvl1_tilemap.png");
	

	col = App->collision->AddCollider({ 0,-250, 1000, 1 },COLLIDER_EXPLOSION, this);//dark line


	
	//App->enemies->AddEnemy(ENEMY_TYPES::GREENSHOOTER_SPACESHIP, 30, -330, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::LIGHTSHOOTER_SPACESHIP, 20, -150, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::LIGHTSHOOTER_SPACESHIP, 100, -250, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::LIGHTSHOOTER_SPACESHIP, 200, -350, 3);
	//App->enemies->AddEnemy(ENEMY_TYPES::LIGHTSHOOTER_SPACESHIP, 200, -1600, 3);
	
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_MEDAL, 30,-100  );
	
	//App->enemies->AddEnemy(ENEMY_TYPES::BONUS_SPACESHIP, 92, -100, 3);
	
	
	return true;
}

// UnLoad assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading level 1");

	App->textures->Unload(graphics);

	App->player->Disable();
	App->player2->Disable();
	App->enemies->Disable();
	App->collision->Disable();
	App->powerup->Disable();
	App->particles->Disable();

	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	
	float scroll_speed = 0.5f;

	App->player->position.y += 1;
	App->render->camera.y += 2;

	// Draw everything --------------------------------------
	App->render->Blit(graphics, -50, -2965, &background); 

	App->render->Blit(graphics, -50, -2965, &foreground);
	
	if (App->player->position.y == -2965) {
		App->fade->FadeToBlack(this, App->stageCompleted);
		fading = true;
	}


	if (App->input->keyboard[SDL_SCANCODE_TAB] && fading == false) {
	
		App->fade->FadeToBlack(this, App->stageCompleted);
		fading = true;
		
	}

	return UPDATE_CONTINUE;
}