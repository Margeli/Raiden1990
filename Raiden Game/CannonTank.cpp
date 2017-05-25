#include "Application.h"
#include "CannonTank.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"


CannonTank::CannonTank(int x, int y, int shoot_num) : Enemy(x, y)
{
	down.PushBack({ 0,29,38,34 });
	up.PushBack({ 38,29,38,34 });
	right.PushBack({ 75,29,38,34 });
	left.PushBack({ 113,29,38,34 });
	down_left.PushBack({ 152,29,38,34 });
	down_right.PushBack({ 190,29,38,34 });
	up_right.PushBack({ 228,29,38,34 });
	up_left.PushBack({ 266,29,38,34 });

	//TankCannon shot
	color_rotatory_shot.anim.PushBack({ 22, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 39, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 56, 40, 6, 7 });
	color_rotatory_shot.anim.speed = 0.3f;
	color_rotatory_shot.life = 3000;
	color_rotatory_shot.anim.loop = true;


	explosion.anim.PushBack({ 0,0,32,30 });
	explosion.anim.PushBack({ 32,0,32,30 });
	explosion.anim.PushBack({ 64,0,32,30 });
	explosion.anim.PushBack({ 96,0,32,30 });
	explosion.anim.PushBack({ 128,0,32,30 });
	explosion.anim.PushBack({ 160,0,32,30 });
	explosion.anim.PushBack({ 192,0,32,30 });
	explosion.anim.PushBack({ 224,0,32,30 });
	explosion.anim.PushBack({ 256,0,32,30 });
	explosion.anim.PushBack({ 288,0,32,30 });
	explosion.anim.PushBack({ 0,0,0,0 });
	explosion.anim.speed = 0.2f;
	explosion.anim.loop = false;
	explosion.life = 1000;


	sprite_path = App->textures->Load("Assets/Images/Tank.png");

	
	if (sprite_path == nullptr) {
		LOG("Error loading CannonTank's textures. SDL Error: %s", SDL_GetError());
	}
	animation = &down;

	shoot_number = shoot_num;
	initial_y = y;
	increment_y = 0.0f;


	
	hits_life = 2.0f;//2.0f
	
	player_initial_x = App->player->position.x; //Stores player position X when tank is spawning.

	collider = App->collision->AddCollider({ 0, 0, 38, 34 }, COLLIDER_TYPE::COLLIDER_BOX, (Module*)App->enemies);

	timer_shot = SDL_GetTicks();

}

void CannonTank::Move() {

	increment_y = (position.y - initial_y);//SAME MOVEMENT AS THE TANK

	if (player_initial_x > position.x) {		
		position.x++;
		speed = 0.1f;

	}
	else if (player_initial_x< position.x) {		
		position.x--;
		speed = 0.1f;
	}
	else {
		speed = 0.0f;
	}

	if ((App->player->position.y-2 > position.y + 34)) {// DOWN

		if ((App->player->position.x > position.x) && (App->player->position.x < position.x + 38)) {
			animation = &down;
		}
		else if (App->player->position.x > position.x-2) {
			animation = &down_right;
		}
		else if (App->player->position.x < position.x + 38) {
			animation = &down_left;
		}
	}
	else if ((App->player->position.y < position.y)) {//UP

		if ((App->player->position.x > position.x) && (App->player->position.x < position.x + 38)) {
			animation = &up;
		}
		else if (App->player->position.x > position.x) {
			animation = &up_right;
		}
		else if (App->player->position.x < position.x + 38) {
			animation = &up_left;
		}
	}
	else if ((App->player->position.y > position.y) && (App->player->position.y < position.y + 34)) {//MIDDLE
		if (App->player->position.x > position.x) {
			animation = &right;
		}
		else if (App->player->position.x < position.x + 38) {
			animation = &left;
		}
	}

	if (SDL_GetTicks() - timer_shot > 2500 && shoot_number>0) {
		Shot(color_rotatory_shot, App->player->position, position);
		timer_shot = SDL_GetTicks();
		shoot_number--;
	}


	position.y += speed;
	collider->SetPos(position.x, position.y);
}




void CannonTank::OnCollision(Collider*collider, int num_enemy) {

	if (collider->type == COLLIDER_PLAYER_SHOT) {
		hits_life -= App->player->hit_dmg;

	}
	else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
		hits_life -= App->player2->hit_dmg;

	}
	else if (collider->type == COLLIDER_BOMB) {
		hits_life -= App->player->bomb_dmg;
	}
	if (hits_life <= 0) {		
		App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);
		fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_Tank_Explosion.wav");
		if (!fx_shoot) {
			LOG("Error loading shoot's fx: %s", Mix_GetError)
		}
		App->audio->Play_Fx(fx_shoot);
		delete App->enemies->enemies[num_enemy];
		App->enemies->enemies[num_enemy] = nullptr;

	}

}

void CannonTank::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {
	shot.speed = { 0,0 };

	if (animation == &up) {
		shot.speed = { 0,-5 };
	}
	else if (animation == &down) {
		shot.speed = { 0,3 };
	}
	else if (animation == &right) {
		shot.speed = { 3,0 };

	}
	else if (animation == &left) {
		shot.speed = { -3,0 };
	}
	else if (animation == &down_right) {
		shot.speed = { 3,3 };

	}
	else if (animation == &down_left) {
		shot.speed = { -3,3 };
	}
	else if (animation == &up_right) {
		shot.speed = { 3,-4 };

	}
	else if (animation == &up_left) {
		shot.speed = { -3,-4 };
	}

	App->particles->AddParticle(shot, shot_initial_pos.x + 19, shot_initial_pos.y + 17, COLLIDER_ENEMY_SHOT);


}