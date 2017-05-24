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
#include "SDL/include/SDL_timer.h"

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;

	//idle animation

	idle.PushBack({ 305, 13, 24,27 });

	//move animation right

	right.PushBack({ 338, 14, 20, 27 });
	right.PushBack({ 372, 14, 15, 27 });
	right.loop = false;
	right.speed = 0.1f;

	//move animation left

	left.PushBack({ 246, 14, 20, 27 });
	left.PushBack({ 275, 14, 15, 27 });
	left.loop = false;
	left.speed = 0.1f;

	//move animation boost

	boost.PushBack({ 147, 619, 24, 32 });
	boost.PushBack({ 178, 619, 24, 32 });

	//Raiden2 basic shot 

	basic_shot.anim.PushBack({ 22, 31, 5, 5 });	//animation
	basic_shot.anim.speed = 1.0f;
	basic_shot.speed.y = -3;
	basic_shot.speed.x = 0;
	basic_shot.life = 1850;
	basic_shot.anim.loop = true;

	//Raiden2 left basic shot 

	left_basic_shot.anim.PushBack({ 22, 31, 5, 5 });
	left_basic_shot.anim.speed = 1.0f;
	left_basic_shot.speed.y = -3;
	left_basic_shot.speed.x = -1;
	left_basic_shot.life = 1850;
	left_basic_shot.anim.loop = true;

	//Raiden2 right basic shot 

	right_basic_shot.anim.PushBack({ 22, 31, 5, 5 });
	right_basic_shot.anim.speed = 1.0f;
	right_basic_shot.speed.y = -3;
	right_basic_shot.speed.x = 1;
	right_basic_shot.life = 1850;
	right_basic_shot.anim.loop = true;

	//Raiden2 triple basic shot 

	triple_shot.anim.PushBack({ 33, 31, 8, 5 });
	triple_shot.anim.speed = 1.0f;
	triple_shot.speed.y = -3;
	triple_shot.speed.x = 0;
	triple_shot.life = 1850;
	triple_shot.anim.loop = true;

	//Raiden2 left triple basic shot 

	left_triple_shot.anim.PushBack({ 33, 31, 8, 5 });
	left_triple_shot.anim.speed = 1.0f;
	left_triple_shot.speed.y = -3;
	left_triple_shot.speed.x = -1;
	left_triple_shot.life = 1850;
	left_triple_shot.anim.loop = true;

	//Raiden2 right triple basic shot 

	right_triple_shot.anim.PushBack({ 33, 31, 8, 5 });
	right_triple_shot.anim.speed = 1.0f;
	right_triple_shot.speed.y = -3;
	right_triple_shot.speed.x = 1;
	right_triple_shot.life = 1850;
	right_triple_shot.anim.loop = true;

	//Raiden2 external right triple basic shot 

	ext_right_triple_shot.anim.PushBack({ 33, 31, 8, 5 });
	ext_right_triple_shot.anim.speed = 1.0f;
	ext_right_triple_shot.speed.y = -3;
	ext_right_triple_shot.speed.x = 2;
	ext_right_triple_shot.life = 1850;
	ext_right_triple_shot.anim.loop = true;

	//Raiden2 external left triple basic shot 

	ext_left_triple_shot.anim.PushBack({ 33, 31, 8, 5 });
	ext_left_triple_shot.anim.speed = 1.0f;
	ext_left_triple_shot.speed.y = -3;
	ext_left_triple_shot.speed.x = -2;
	ext_left_triple_shot.life = 1850;
	ext_left_triple_shot.anim.loop = true;

	//Raiden2 bomb

	bomb.anim.PushBack({ 552,171,8,16 });
	bomb.anim.PushBack({ 564,171,8,16 });
	bomb.anim.PushBack({ 575,171,8,16 });
	bomb.anim.PushBack({ 585,171,8,16 });
	bomb.anim.PushBack({ 595,171,8,16 });
	bomb.anim.PushBack({ 605,171,8,16 });
	bomb.anim.PushBack({ 615,171,8,16 });
	bomb.anim.PushBack({ 626,171,8,16 });
	bomb.anim.speed = 0.08f;
	bomb.speed.y = -2.5f;
	bomb.speed.x = 0.;
	bomb.life = 1300;
	bomb.anim.loop = true;

	//Raiden2 misile shot 

	misile_left.anim.PushBack({ 359, 170, 6, 15 });
	misile_left.anim.PushBack({ 376, 170, 6, 15 });
	misile_left.anim.speed = 1.0f;
	misile_left.speed.y = -4.5f;
	misile_left.speed.x = 0;
	misile_left.life = 1500;
	misile_left.anim.loop = true;

	misile_right.anim.PushBack({ 359, 170, 6, 15 });
	misile_right.anim.PushBack({ 376, 170, 6, 15 });
	misile_right.anim.speed = 1.0f;
	misile_right.speed.y = -4.5f;
	misile_right.speed.x = 0;
	misile_right.life = 1500;
	misile_right.anim.loop = true;

	misile_mid.anim.PushBack({ 359, 170, 6, 15 });
	misile_mid.anim.PushBack({ 376, 170, 6, 15 });
	misile_mid.anim.speed = 0;
	misile_mid.speed.y = -4.5f;
	misile_mid.speed.x = 0;
	misile_mid.life = 1500;
	misile_mid.anim.loop = true;

	//Raiden2 laser shot 

	laser_shot.anim.PushBack({ 309, 132, 1, 15 });
	laser_shot.anim.speed = 1.0f;
	laser_shot.speed.y = -7;
	laser_shot.speed.x = 0;
	laser_shot.life = 700;
	laser_shot.anim.loop = true;

	//Raiden2 big laser shot 

	big_laser_shot.anim.PushBack({ 256, 132, 4, 15 });
	big_laser_shot.anim.speed = 1.0f;
	big_laser_shot.speed.y = -7;
	big_laser_shot.speed.x = 0;
	big_laser_shot.life = 700;
	big_laser_shot.anim.loop = true;

	hit_dmg = 1.0f;
	bomb_dmg = 20.0f;

	dead_explosion.anim.PushBack({ 7,202,32,30 });
	dead_explosion.anim.PushBack({ 40,202,32,30 });
	dead_explosion.anim.PushBack({ 76,202,32,30 });
	dead_explosion.anim.PushBack({ 116,202,32,30 });
	dead_explosion.anim.PushBack({ 164,202,32,30 });
	dead_explosion.anim.PushBack({ 0,0,0,0 });
	dead_explosion.anim.speed = 0.1f;
	dead_explosion.life = 1000;

	//Raiden2 Bomb Explosion
	bomb_explosion.anim.PushBack({ 0, 633, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 633, 168, 154 });
	bomb_explosion.anim.PushBack({ 336, 633, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 633, 168, 154 });
	bomb_explosion.anim.PushBack({ 0, 790, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 790, 168, 154 });
	bomb_explosion.anim.PushBack({ 336, 790, 168, 154 });
	bomb_explosion.anim.PushBack({ 505, 790, 168, 154 });
	bomb_explosion.anim.PushBack({ 0, 941, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 941, 168, 154 });//
	bomb_explosion.anim.PushBack({ 336, 941, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 941, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 941, 168, 154 });//
	bomb_explosion.anim.PushBack({ 336, 941, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 941, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 941, 168, 154 });//
	bomb_explosion.anim.PushBack({ 336, 941, 168, 154 });
	bomb_explosion.anim.PushBack({ 505, 941, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 941, 168, 154 });//
	bomb_explosion.anim.PushBack({ 336, 941, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 941, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 941, 168, 154 });//
	bomb_explosion.anim.PushBack({ 336, 941, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 941, 168, 154 });
	bomb_explosion.anim.PushBack({ 168, 941, 168, 154 });//
	bomb_explosion.anim.PushBack({ 336, 941, 168, 154 });
	bomb_explosion.anim.PushBack({ 504, 941, 168, 154 });
	bomb_explosion.anim.speed = 0.1f;
	bomb_explosion.life = 3000;
	bomb_explosion.anim.loop = false;

}

ModulePlayer2::~ModulePlayer2()
{}

bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player2");

	App->textures->Unload(graphics);
	App->fonts->UnLoad(yellow_font_score);
	App->fonts->UnLoad(red_font_score);

	return true;
}

// Load assets
bool ModulePlayer2::Start()
{
	App->collision->Enable();
	LOG("Loading player 2 textures");
	bool ret = true;

	graphics = App->textures->Load("Assets/Images/Raiden_Spaceship.png");
	if (graphics == nullptr) {
		LOG("Error loading player 2 textures %s", SDL_GetError);
		ret = false;
	}

	position.x = 151;
	position.y = 150;

	current_animation = &idle;
	godmode_activated = " G ";
	user_interface = "    1UP   HI.SCORE    2UP ";
	red_font_score = App->fonts->Load("Assets/Images/Font.png", "> ?@ABCDEFGHIJKLMNOPQRSTUVWXYZ!¡?_*#$%&'()x+.-,;[].{.}/0123456789:", 3);
	yellow_font_score = App->fonts->Load("Assets/Images/Font.png", "> ?@ABCDEFGHIJKLMNOPQRSTUVWXYZ!¡?_*#$%&'()x+.-,;[].{.}/0123456789:", 3);
	// * -> "
	// [ -> tm
	//	]. -> Pts
	//	{. -> Cts
	//	}. -> Pcs

	if (spaceship_collider == nullptr)
		spaceship_collider = App->collision->AddCollider({ 0,0, 24, 26 }, COLLIDER_PLAYER, this);

	total_bombs = 3;
	bomb_thrown = 0;
	bomb_life = 0;
	last_bomb = 0;

	return ret;
}

// Update: draw background
update_status ModulePlayer2::Update()
{

	int spaceship_speed = 1;
	position.y -= spaceship_speed;
	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT) //---UP
	{
		position.y -= speed;
		if (-position.y*SCREEN_SIZE > App->render->camera.y) {
			position.y = -App->render->camera.y / SCREEN_SIZE; //upper player limit. ------->The relation between camera.y and position.y is camera.y=-position.y*SCREEN_SIZE
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)//---DOWN
	{
		position.y += speed;
		if ((-(position.y - SCREEN_HEIGHT + 27)*SCREEN_SIZE)<App->render->camera.y) { //lower player limit (27 is height of spaceship)
			position.y = ((-App->render->camera.y / SCREEN_SIZE) - 27 + SCREEN_HEIGHT);
		}

	}


	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)//---LEFT
	{
		position.x -= speed;
		App->render->camera.x += 4;
		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
		if (App->render->camera.x >= 100) {//left camera limit
			App->render->camera.x = 100;
			if (position.x <= -48) { //left player limit
				position.x = -48;
			}
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)//---RIGHT
	{
		position.x += speed;
		App->render->camera.x -= 4;
		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
		if (App->render->camera.x <= -154) {//right camera limit
			App->render->camera.x = -154;
			if (position.x >= 275) { //right player limit
				position.x = 275;
			}
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE //check error
		&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE) {
		current_animation = &idle;
	}

	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)//GOD MODE
	{
		if (spaceship_collider != nullptr) {
			spaceship_collider->SetPos(-1000, -1000);
			spaceship_collider = nullptr;
			godmode = true;
		}
		else {
			spaceship_collider = App->collision->AddCollider({ 0,0, 23, 26 }, COLLIDER_PLAYER, this);

			godmode = false;
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(basic_shot, position.x + 9, position.y, COLLIDER_PLAYER2_SHOT, 0, "Assets/Audio/Fx_Simple_Shot.wav");//Adds a particle (basic_shot) in front of the spaceship.
	}

	if (spaceship_collider != nullptr)
		spaceship_collider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}
void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
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

	case COLLIDER_POWERUP_BLUE:
		Blue_Powerup_Lvl++;
		if (Blue_Powerup_Lvl >= 5) {
			Blue_Powerup_Lvl = 4;
			score += 5000;
		}
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
		if (M_Powerup_Lvl >= 4) {
			M_Powerup_Lvl = 3;
			score += 5000;
		}
		break;
	case COLLIDER_POWERUP_B:
		total_bombs++;
		if (total_bombs >= 6) {
			total_bombs = 6;
		}
		break;

	case COLLIDER_ENEMY_SHOT:
		if (c1 == spaceship_collider && destroyed == false && App->fade->IsFading() == false && godmode == false) {
			Dead();
		}
	case COLLIDER_ENEMY:
		if (c1 == spaceship_collider && destroyed == false && App->fade->IsFading() == false && godmode == false) {
			Dead();
		}

	}
	
}

void ModulePlayer2::Dead() {

	Red_Powerup_Lvl = 0;
	M_Powerup_Lvl = 0;
	Blue_Powerup_Lvl = 0;
	sprintf_s(score_text, 10, "%8d", score);
	sprintf_s(high_score_text, 10, "%7d", high_score);

	destroyed = true;

	App->player->player1 = false;
	App->fade->FadeToBlack((Module*)App->level1, (Module*)App->intro);
	App->particles->AddParticle(dead_explosion, position.x, position.y, COLLIDER_EXPLOSION, 0, "Assets/Audio/Fx_Player_Explosion.wav");
	App->textures->Unload(graphics);
}