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
	App->level2->Disable();
	App->stageCompleted->Disable();

	App->audio->Enable();
	App->collision->Enable();
	App->player->Enable();
	if (App->player2->player2 == true)
		App->player2->Enable();
	else if (App->player2->player2)
		App->player2->Disable();
	App->particles->Enable();
	
	App->enemies->Enable();

	if (App->player2->player2 == false) {

		App->player->position.x = 111; //position if there's only 1 player
		App->player->position.y = 150;
	}
	else {

		App->player->position.x = 71; //position if there are 2 players
		App->player->position.y = 150;
	}
	if ((!App->player->godmode)&&(App->player->spaceship_collider->rect.w<-1000)){ //SOLVES AN ERROR THAT THE COLLIDER OF RAIDEN HAS -572662307 of x, y, w & h
		App->player->spaceship_collider = App->collision->AddCollider({ 0,0, 23, 26 }, COLLIDER_PLAYER, App->player);
	App->player->spaceship_collider->SetPos(App->player->position.x, App->player->position.y);
}

	

	
	
	LOG("Loading level 1");

	music_lvl1 = App->audio->Load_Music("Assets/Audio/00_Raiden.ogg");// UNCOMMENT FOR PLAYING MUSIC
	if (!music_lvl1) {
	LOG("Error loading lvl1 music: %s",Mix_GetError)
	}
	App->audio->Play_Music(music_lvl1);
	
	graphics = App->textures->Load("Assets/Images/lvl1_tilemap.png");
	

	col = App->collision->AddCollider({ 0,0, 1000, 1 },COLLIDER_EXPLOSION, this);//dark line


	


	
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_M, 60,-500);
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_MEDAL, 60,-420);
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_MEDAL, 150, -660);
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_MEDAL, 170, -680);
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_MEDAL, 150, -680);
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_MEDAL, 170, -660);
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_MEDAL, 240, -900);
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_MEDAL, 20, -940);

	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 60, -170, 0);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 160, -225, 0);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 180, -235, 0);
	App->enemies->AddEnemy(BONUS_SPACESHIP, 111, -240, 0); // just in the middle
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 60, -430, 0);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 111, -460, 0);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 180, -480, 0);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 200, -500, 0);
	App->enemies->AddEnemy(GREENSHOOTER_SPACESHIP, 80, -650, 3);
	App->enemies->AddEnemy(GREENSHOOTER_SPACESHIP, 180, -800, 3);
	App->enemies->AddEnemy(GREENSHOOTER_SPACESHIP, 111, -850, 3);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 111, -1000, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 160, -1100, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 180, -1150, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 100, -1250, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 120, -1300, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 140, -1350, 1);
	App->enemies->AddEnemy(BONUS_SPACESHIP, 111, -1400, 3); // just in the middle
	App->enemies->AddEnemy(GREENSHOOTER_SPACESHIP, 80, -1800, 3);
	App->enemies->AddEnemy(GREENSHOOTER_SPACESHIP, 190, -1800, 3);

	



	App->enemies->AddEnemy(ENEMY_TYPES::LIGHTSHOOTER_SPACESHIP, 50, -150, 0);
	
	

	
	
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
	
	if (App->player->position.y == -2925) {
		App->fade->FadeToBlack(this, App->stageCompleted);
		fading = true;
	}


	/*if (App->input->keyboard[SDL_SCANCODE_TAB] && fading == false) {
	
		App->fade->FadeToBlack(this, App->stageCompleted);
		fading = true;
		
	}*/

	return UPDATE_CONTINUE;
}