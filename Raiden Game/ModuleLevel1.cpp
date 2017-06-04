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
	foreground.h = 2836;

	// Background / sky
	background.x = 0;
	background.y = 134;
	background.w = 351;
	background.h = 3265;

	ship_launcher.x = 352;
	ship_launcher.y = 2971;
	ship_launcher.w = 351;
	ship_launcher.h = 429;

	
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

	if ((App->player->spaceship_collider == nullptr) && (App->player->godmode == false)) {
		App->player->spaceship_collider = App->collision->AddCollider({ 0,0, 23, 26 }, COLLIDER_PLAYER, App->player);
		App->player->spaceship_collider->SetPos(App->player->position.x, App->player->position.y);
	}

	scroll_speed = 2;
	
	LOG("Loading level 1");

	music_lvl1 = App->audio->Load_Music("Assets/Audio/00_Raiden.ogg");// COMMENT TO STOP MUSIC
	if (!music_lvl1) {
	LOG("Error loading lvl1 music: %s",Mix_GetError)
	}
	App->audio->Play_Music(music_lvl1);
	
	graphics = App->textures->Load("Assets/Images/lvl1_tilemap.png");
	
	App->enemies->AddEnemy(BOSS, 224, -2968);
	App->enemies->AddEnemy(BOSS2, 87, -2700);


	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_M, 60, -500);
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_M, 60, -1000);
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_M, 60, -2000);
	App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_B, 60, -1500);
	App->enemies->AddEnemy(BOX, 150, -660);
	App->enemies->AddEnemy(BOX, 172, -682);
	App->enemies->AddEnemy(BOX, 150, -682);
	App->enemies->AddEnemy(BOX, 172, -660);
	App->enemies->AddEnemy(BOX, 240, -900);
	App->enemies->AddEnemy(BOX, 20, -940);


	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 60, -190, 0);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 160, -245, 0);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 180, -255, 0);
	App->enemies->AddEnemy(BONUS_SPACESHIP, 111, -260, 0); // just in the middle

	App->enemies->AddEnemy(TANK, 60, -450, 0);
	App->enemies->AddEnemy(TANK, 100, -490, 1);
	App->enemies->AddEnemy(TANK, 140, -530, 0);
	App->enemies->AddEnemy(TANK, 180, -570, 1);
	App->enemies->AddEnemy(STATIC_CANNON, 210, -600, 3);
	App->enemies->AddEnemy(STATIC_CANNON, 80, -600, 3);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 160, -700, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 70, -770, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 130, -810, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 160, -850, 1);
	App->enemies->AddEnemy(GREENSHOOTER_SPACESHIP, 60, -550, 3);
	App->enemies->AddEnemy(GREENSHOOTER_SPACESHIP, 170, -650, 3);
	App->enemies->AddEnemy(GREENSHOOTER_SPACESHIP, 111, -750, 3);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 60, -660, 1);
	App->enemies->AddEnemy(TANK, 20, -800, 1);
	App->enemies->AddEnemy(TANK, 40, -820, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 60, -1000, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 100, -1000, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 80, -1050, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 140, -1150, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 111, -1200, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 160, -1250, 1);
	App->enemies->AddEnemy(TANK, 50, -1350, 2);
	App->enemies->AddEnemy(BONUS_SPACESHIP, 111, -1400, 3);
	App->enemies->AddEnemy(STATIC_CANNON, 120, -1500, 1);
	App->enemies->AddEnemy(TANK, 160, -1600, 2);
	App->enemies->AddEnemy(TANK, 30, -1550, 2);
	App->enemies->AddEnemy(TANK, 40, -1650, 2);
	App->enemies->AddEnemy(TANK, 120, -1650, 2);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 160, -1750, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 100, -1750, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 40, -1800, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 140, -1830, 1);
	App->enemies->AddEnemy(MINE, 110, -1860, 1);
	App->enemies->AddEnemy(TANK, 20, -1860, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 20, -1860, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 70, -1900, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 120, -1950, 1);
	App->enemies->AddEnemy(LIGHTSHOOTER_SPACESHIP, 110, -1900, 1);
	App->enemies->AddEnemy(BONUS_SPACESHIP, 111, -2000, 3); // just in the middle
	App->enemies->AddEnemy(STATIC_CANNON, 80, -2000, 3);
	App->enemies->AddEnemy(STATIC_CANNON, 190, -2030, 3);
	App->enemies->AddEnemy(STATIC_CANNON, 120, -2100, 3);
	App->enemies->AddEnemy(STATIC_CANNON, 40, -2050, 3);

	App->enemies->AddEnemy(ENEMY_TYPES::MEGA_TANK, 0, -2500, 3, true);	// <---- NO BORRAR COORDENADAS "X", ESTÁN EXACTAS (SIEMPRE SALEN LOS DOS A LA VEZ)
	App->enemies->AddEnemy(ENEMY_TYPES::MEGA_TANK, 177, -2500, 3, false); // <----´
	App->enemies->AddEnemy(ENEMY_TYPES::HEAVY_SHOOTER, 0, -2700, 3, true);	// <---- NO BORRAR COORDENADAS "X", ESTÁN EXACTAS (SIEMPRE SALEN LOS DOS A LA VEZ)
	App->enemies->AddEnemy(ENEMY_TYPES::HEAVY_SHOOTER, 177, -2700, 3, false); // <----´
	App->enemies->AddEnemy(MINE, 30, -2300, 2);
	App->enemies->AddEnemy(MINE, 70, -2300, 2);
	App->enemies->AddEnemy(MINE, 100, -2300, 2);
	App->enemies->AddEnemy(MINE, 130, -2300, 2);
	App->enemies->AddEnemy(MINE, 170, -2300, 2);
	return true;
}

// UnLoad assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading level 1");

	

	if (graphics != nullptr)	
		App->textures->Unload(graphics);
	if (music_lvl1 != nullptr) 	
		App->audio->Unload_Music(music_lvl1);
	App->player->Disable();
	App->player2->Disable();
	App->enemies->Disable();
	//App->collision->Disable();
	App->powerup->Disable();
	App->particles->Disable();

	first_animation = false;


	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	

	if (App->render->camera.y < 100) {
		
		App->player->position.y += 1;
		App->player2->position.y += 1;
		App->render->camera.y += 1;
		first_animation = true;

	}
	else {
		if (App->render->camera.y < 220) {
			App->player->current_animation = &App->player->boost;
			App->player2->current_animation = &App->player2->boost;
		}
		else {
			first_animation = false;
		}
		App->render->camera.y += scroll_speed;
		
		if ((App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN) && (App->fade->IsFading() == false))//DIRECT WIN/LOSE
		{
			App->fade->FadeToBlack(this, App->stageCompleted);

		}
	
	}

	// Draw everything --------------------------------------
	
	App->render->Blit(graphics, -50, -2965, &background); 

	App->render->Blit(graphics, -50, -2965, &foreground);
	
	App->render->Blit(graphics, -50, -150, &ship_launcher, 1.8f);


	if (App->player->position.y <= -2735) {

		scroll_speed = 0;
 		boss_music = App->audio->Load_Music("Assets/Audio/Boss_Music.ogg");
		if (!boss_music) {
			LOG("Error loading boss music: %s", Mix_GetError)
		}
		/*App->audio->Play_Music(boss_music);
		App->player->spaceship_speed = 0;
<<<<<<< HEAD
		/*if (App->player2->IsEnabled) 
			App->player2->spaceship_speed = 0;*/

		if (App->player2->IsEnabled()) 
			App->player2->spaceship_speed = 0;



	/*if (App->input->keyboard[SDL_SCANCODE_TAB] && fading == false) {
	
		App->fade->FadeToBlack(this, App->stageCompleted);
		fading = true;
		*/
	}

	return UPDATE_CONTINUE;
}