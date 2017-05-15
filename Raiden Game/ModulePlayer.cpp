#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleStageCompleted.h"
#include "ModuleLevel1.h"

#include<stdio.h>

ModulePlayer::ModulePlayer()
{
	
	
	graphics = NULL;
	current_animation = NULL;
	shadow_animation = NULL;

	//Player image

	idle.PushBack({ 80, 13, 24, 27 });


	//move animation boost

	boost.PushBack({ 147, 619, 24, 32 });
	boost.PushBack({ 178, 619, 24, 32 });

	//move animation right 
	
	right.PushBack({ 114, 14, 20, 27 });
	right.PushBack({ 149, 14, 15, 27 });
	right.loop = false;
	right.speed = 0.05f;

	//move animation left
	
	left.PushBack({ 51, 14, 20, 27 });
	left.PushBack({ 22, 14, 15, 27 });
	left.loop = false;
	left.speed = 0.05f;

	//shadow image
	shadow_idle.PushBack({ 15, 657, 12, 8 });

	//shadow animation right
	shadow_right.PushBack({ 64, 71, 12, 8 });
	shadow_right.PushBack({ 81, 71, 12, 8 });
	shadow_right.loop = false;
	shadow_right.speed = 0.05f;

	//shadow animation left
	shadow_left.PushBack({ 29, 657, 12, 8 });
	shadow_left.PushBack({ 43, 657, 12, 8 });
	shadow_left.loop = false;
	shadow_left.speed = 0.05f;

	//Raiden basic shot 
	
	basic_shot.anim.PushBack({ 22, 31, 5, 5 });	//animation
	basic_shot.anim.speed = 1.0f;
	basic_shot.speed.y = -3;
	basic_shot.speed.x = 0;
	basic_shot.life = 1850;
	basic_shot.anim.loop = true;

	//Raiden left basic shot 

	left_basic_shot.anim.PushBack({ 22, 31, 5, 5 });	//animation
	left_basic_shot.anim.speed = 1.0f;
	left_basic_shot.speed.y = -3;
	left_basic_shot.speed.x = -1;
	left_basic_shot.life = 1850;
	left_basic_shot.anim.loop = true;

	//Raiden right basic shot 

	right_basic_shot.anim.PushBack({ 22, 31, 5, 5 });	//animation
	right_basic_shot.anim.speed = 1.0f;
	right_basic_shot.speed.y = -3;
	right_basic_shot.speed.x = 1;
	right_basic_shot.life = 1850;
	right_basic_shot.anim.loop = true;

	//Raiden triple basic shot 

	triple_shot.anim.PushBack({ 33, 31, 8, 5 });	//animation
	triple_shot.anim.speed = 1.0f;
	triple_shot.speed.y = -3;
	triple_shot.speed.x = 0;
	triple_shot.life = 1850;
	triple_shot.anim.loop = true;

	//Raiden left triple basic shot 

	left_triple_shot.anim.PushBack({ 33, 31, 8, 5 });	//animation
	left_triple_shot.anim.speed = 1.0f;
	left_triple_shot.speed.y = -3;
	left_triple_shot.speed.x = -1;
	left_triple_shot.life = 1850;
	left_triple_shot.anim.loop = true;

	//Raiden right triple basic shot 

	right_triple_shot.anim.PushBack({ 33, 31, 8, 5 });	//animation
	right_triple_shot.anim.speed = 1.0f;
	right_triple_shot.speed.y = -3;
	right_triple_shot.speed.x = 1;
	right_triple_shot.life = 1850;
	right_triple_shot.anim.loop = true;

	//Raiden external right triple basic shot 

	ext_right_triple_shot.anim.PushBack({ 33, 31, 8, 5 });	//animation
	ext_right_triple_shot.anim.speed = 1.0f;
	ext_right_triple_shot.speed.y = -3;
	ext_right_triple_shot.speed.x = 2;
	ext_right_triple_shot.life = 1850;
	ext_right_triple_shot.anim.loop = true;

	//Raiden external left triple basic shot 

	ext_left_triple_shot.anim.PushBack({ 33, 31, 8, 5 });	//animation
	ext_left_triple_shot.anim.speed = 1.0f;
	ext_left_triple_shot.speed.y = -3;
	ext_left_triple_shot.speed.x = -2;
	ext_left_triple_shot.life = 1850;
	ext_left_triple_shot.anim.loop = true;

	//Raiden misile shot 

	misile_left.anim.PushBack({ 411, 169, 6, 15 });
	misile_left.anim.PushBack({ 428, 169, 6, 15 });
	misile_left.anim.speed = 1.0f;
	misile_left.speed.y = -4.5f;
	misile_left.speed.x = 0;
	misile_left.life = 1850;
	misile_left.anim.loop = true;

	misile_right.anim.PushBack({ 411, 169, 6, 15 });
	misile_right.anim.PushBack({ 428, 169, 6, 15 });
	misile_right.anim.speed = 1.0f;
	misile_right.speed.y = -4.5f;
	misile_right.speed.x = 0;
	misile_right.life = 1850;
	misile_right.anim.loop = true;

	hit_dmg = 1.0f;

	dead_explosion.anim.PushBack({ 7,202,32,30 });
	dead_explosion.anim.PushBack({ 40,202,32,30 });
	dead_explosion.anim.PushBack({ 76,202,32,30 });
	dead_explosion.anim.PushBack({ 116,202,32,30 });
	dead_explosion.anim.PushBack({ 164,202,32,30 });
	dead_explosion.anim.PushBack({ 0,0,0,0 });
	dead_explosion.anim.speed = 0.1f;
	dead_explosion.life = 1000;
	
	//Raiden Bomb Explosion
	bomb_explosion.anim.PushBack({ 0, 633, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 633, 168, 154 });
	bomb_explosion.anim.PushBack({ 336, 633, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 633, 168, 154 });
	bomb_explosion.anim.PushBack({ 0, 801, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 801, 168, 154 });
	bomb_explosion.anim.PushBack({ 336, 801, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 801, 168, 154 });
	bomb_explosion.anim.PushBack({ 0, 969, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 969, 168, 154 });//
	bomb_explosion.anim.PushBack({ 336, 969, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 969, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 969, 168, 154 });//
	bomb_explosion.anim.PushBack({ 336, 969, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 969, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 969, 168, 154 });//
	bomb_explosion.anim.PushBack({ 336, 969, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 969, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 969, 168, 154 });//
	bomb_explosion.anim.PushBack({ 336, 969, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 969, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 969, 168, 154 });//
	bomb_explosion.anim.PushBack({ 336, 969, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 969, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 969, 168, 154 });//
	bomb_explosion.anim.PushBack({ 336, 969, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 969, 168, 154 });
	bomb_explosion.anim.speed = 0.4f;
	bomb_explosion.life = 2500;
	
}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->fonts->UnLoad(yellow_font_score);
	App->fonts->UnLoad(red_font_score);
	/*if (spaceship_collider != nullptr) {
	spaceship_collider->to_delete = true;
	}*/

	return true;
}

// Load assets
bool ModulePlayer::Start()
{
	App->collision->Enable();
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Images/Raiden_Spaceship.png"); 
	if (graphics == nullptr) {
		LOG("Error loading player textures %s", SDL_GetError);
		ret = false;
	}
	
	if (App->player2->player2==false) { 

		position.x = 111; //position if there's only 1 player
		position.y = 150;

		shadow_position.x = 118;
		shadow_position.y = 150;
	}
	else {

		position.x = 71; //position if there are 2 players
		position.y = 150;

	}
	current_animation = &idle;
	shadow_animation = &shadow_idle;
	godmode_activated = " G ";
	user_interface = "    1UP   HI.SCORE    2UP ";
	red_font_score = App->fonts->Load("Assets/Images/Font.png", "> ?@ABCDEFGHIJKLMNOPQRSTUVWXYZ!¡?_*#$%&'()x+.-,;[].{.}/0123456789:", 3);
	yellow_font_score = App->fonts->Load("Assets/Images/Font.png", "> ?@ABCDEFGHIJKLMNOPQRSTUVWXYZ!¡?_*#$%&'()x+.-,;[].{.}/0123456789:", 3);
	// * -> "
	// [ -> tm
	//	]. -> Pts
	//	{. -> Cts
	//	}. -> Pcs

	if (spaceship_collider==nullptr)
	spaceship_collider = App->collision->AddCollider({ 0,0, 24, 26 }, COLLIDER_PLAYER, this);

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	
	int speed = 2;
	int spaceship_speed = 1;
	position.y -= spaceship_speed;

	if (!App->level1->first_animation) {// not able to move during first animation
		if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT|| App->input->gamepad[0] == KEY_STATE::KEY_REPEAT) //---UP
		{
			position.y -= speed;
			if (-position.y*SCREEN_SIZE > App->render->camera.y) {
				position.y = -App->render->camera.y / SCREEN_SIZE; //upper player limit. ------->The relation between camera.y and position.y is camera.y=-position.y*SCREEN_SIZE
			}

		}


		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT|| App->input->gamepad[1] == KEY_STATE::KEY_REPEAT)//---DOWN
		{
			position.y += speed;
			if ((-(position.y-SCREEN_HEIGHT+27)*SCREEN_SIZE)<App->render->camera.y) { //lower player limit (27 is height of spaceship)
				position.y = ((-App->render->camera.y / SCREEN_SIZE) -27+ SCREEN_HEIGHT) ;
			}

		
			}
		
	
		shadow_animation = &shadow_idle;

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT|| App->input->gamepad[3] == KEY_STATE::KEY_REPEAT)//---LEFT

		{
			position.x -= speed;
			App->render->camera.x +=4;
			if (current_animation != &left)
			{
				left.Reset();
				current_animation = &left;
				shadow_animation = &shadow_left;
			}
			if (App->render->camera.x >= 100) {//left camera limit
				App->render->camera.x = 100;
				if (position.x <= -48) { //left player limit
					position.x = -48;
				}
			}			
		}
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN|| App->input->gamepad[4] == KEY_STATE::KEY_DOWN)// --SPACE SHOT
		{
			switch (Red_Powerup_Lvl)
			{
			case 0:
				App->particles->AddParticle(basic_shot, position.x + 9, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Simple_Shot.wav");//Adds a particle (basic_shot) in front of the spaceship.
				break;
			case 1:
				App->particles->AddParticle(basic_shot, position.x + 5, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Red_Powerup_Shot.wav"); // Adds 2 particles
				App->particles->AddParticle(basic_shot, position.x + 13, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Red_Powerup_Shot.wav");
				break;
			case 2:
				App->particles->AddParticle(left_basic_shot, position.x + 3, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Red_Powerup_Shot.wav"); // Adds 3 particles
				App->particles->AddParticle(right_basic_shot, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Red_Powerup_Shot.wav");
				App->particles->AddParticle(basic_shot, position.x + 9, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Red_Powerup_Shot.wav");
				break;
			case 3:
				App->particles->AddParticle(left_triple_shot, position.x + 3, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Red_Powerup_Shot.wav"); // Adds 3 particles (triple)
				App->particles->AddParticle(right_triple_shot, position.x + 15, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Red_Powerup_Shot.wav");
				App->particles->AddParticle(triple_shot, position.x + 9, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Red_Powerup_Shot.wav");
				break;
			case 4:
				App->particles->AddParticle(left_triple_shot, position.x + 5, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Red_Powerup_Shot.wav"); // Adds 5 particles (triple)
				App->particles->AddParticle(right_triple_shot, position.x + 13, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Red_Powerup_Shot.wav");
				App->particles->AddParticle(triple_shot, position.x + 9, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Red_Powerup_Shot.wav");
				App->particles->AddParticle(ext_left_triple_shot, position.x + 1, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Red_Powerup_Shot.wav"); 
				App->particles->AddParticle(ext_right_triple_shot, position.x + 17, position.y, COLLIDER_PLAYER_SHOT, 0, "Assets/Audio/Fx_Red_Powerup_Shot.wav");
				break;
			
			}
			switch (Blue_Powerup_Lvl)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
		
			}
			switch (M_Powerup_Lvl)
			{
			case 0:
				break;
			case 1:
				App->particles->AddParticle(misile_left, position.x, position.y, COLLIDER_PLAYER_SHOT, 0);
				App->particles->AddParticle(misile_right, position.x + 24, position.y, COLLIDER_PLAYER_SHOT, 0);
				break;
			case 2:
				break;
			case 3:
				break;
			
			}	
			
		}


		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT|| App->input->gamepad[2] == KEY_STATE::KEY_REPEAT)//---RIGHT

		{
			position.x += speed;
			App->render->camera.x -= 4;
			if (current_animation != &right)
			{
				right.Reset();
				current_animation = &right;
				shadow_animation = &shadow_right;
			}
			if (App->render->camera.x <= -154) {//right camera limit
				App->render->camera.x =-154;
				if (position.x >= 275) { //right player limit
					position.x = 275;
				}
			}
		}
	 
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE //check error
			&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE&&!App->level1->first_animation) {
			current_animation = &idle;
			shadow_animation = &idle;
		}
	}


	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN|| App->input->gamepad[5] == KEY_STATE::KEY_REPEAT)//GOD MODE (press right stick on controller)

	{
		if (!godmode){			
			godmode = true;
		}
		else {			
			godmode = false;
		}				
	}
	if( (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)&&(App->fade->IsFading()==false))//DIRECT WIN/LOSE
	{
		App->fade->FadeToBlack(this, App->stageCompleted);		

	}
	



	if (spaceship_collider!= nullptr)
		spaceship_collider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
		// Draw UI (score) --------------------------------------

		if (score >= high_score)
			high_score = score;

		//Draw shadows

		
		sprintf_s(score_text, 10, "%8d", score);
		sprintf_s(high_score_text, 10, "%7d", high_score);
		
		App->fonts->BlitText(0,1,red_font_score, user_interface);
		App->fonts->BlitText(0, 9, yellow_font_score, score_text);
		App->fonts->BlitText(88,9,yellow_font_score, high_score_text);
		if (godmode) {
			App->fonts->BlitText(0, 1, yellow_font_score, godmode_activated);// Yellow "G" in left upper corner when godmode activated.
		}

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	switch (c2->type) {
	case COLLIDER_POWERUP_MEDAL:
		//App->particles->AddParticle(bonus_medal, position.x + 9, position.y, COLLIDER_PLAYER, 0, "Assets/Audio/Fx_Medal_Bonus.wav");
		score += 500;	
		fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_Medal_Bonus.wav");
			if (!fx_shoot) {
				LOG("Error loading shoot's fx: %s", Mix_GetError)
			}
			App->audio->Play_Fx(fx_shoot);
			
		
		break;

	case COLLIDER_POWERUP_R:
		Red_Powerup_Lvl++;
		if (Red_Powerup_Lvl >= 5) {
			Red_Powerup_Lvl = 4;
			score += 5000;
		}
		break;
	case COLLIDER_POWERUP_M:
		M_Powerup_Lvl++;
		if (Red_Powerup_Lvl >= 4) {
			Red_Powerup_Lvl = 3;
			score += 5000;
		}
		break;

	case COLLIDER_ENEMY_SHOT :
		if (c1 == spaceship_collider && destroyed == false && App->fade->IsFading() == false&&godmode==false) {
			Dead();
		}
	case COLLIDER_ENEMY:
		if (c1 == spaceship_collider && destroyed == false && App->fade->IsFading() == false && godmode==false ) {
			Dead();
		}

	}
}

void ModulePlayer::Dead() {

	
	
	Red_Powerup_Lvl = 0;
	M_Powerup_Lvl = 0;
	Blue_Powerup_Lvl = 0;
	sprintf_s(score_text, 10, "%8d", score);
	sprintf_s(high_score_text, 10, "%7d", high_score);
	
	destroyed = true;
	
	App->player2->player2 = false;
	App->fade->FadeToBlack((Module*)App->level1, (Module*)App->intro);
	App->particles->AddParticle(dead_explosion, position.x, position.y, COLLIDER_EXPLOSION,0, "Assets/Audio/Fx_Player_Explosion.wav");
	App->textures->Unload(graphics);
		
}