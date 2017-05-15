#include "Application.h"
#include "MegaTank.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

MegaTank::MegaTank(int x, int y, bool right) : Enemy(x, y)
{
	sprite_path = App->textures->Load("Assets/Images/Mega_Tank.png");

	if (sprite_path == nullptr) {
		LOG("Error loading GreenShooter's textures. SDL Error: %s", SDL_GetError());
	}

	idle_forward.PushBack({ 0,0,47,48 });
	forward.PushBack({ 0, 0, 47, 48 });
	forward.PushBack({ 49, 0, 47, 48 });
	forward.PushBack({ 99, 0, 47, 48 });
	forward.speed = 0.2f;

	idle_side.PushBack({ 0, 48, 47, 48 });
	sideward.PushBack({ 0, 48, 47, 48 });
	sideward.PushBack({ 49, 48, 47, 48 });
	sideward.PushBack({ 99, 48, 47, 48 });
	sideward.speed = 0.2f;

	score_points = 1120;//1120
	hits_life = 30.0f;//30

	collider = App->collision->AddCollider({ 0, 0, 47, 48 }, COLLIDER_TYPE::COLLIDER_BOX, (Module*)App->enemies); // collider type box because the tank is in the ground, so there is no damage for touching with the player's collider
		
	initial.x = x;
	initial.y = y;

	//Mine explosion shot
	color_rotatory_shot.anim.PushBack({ 22, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 39, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 56, 40, 6, 7 });//animation
	color_rotatory_shot.anim.speed = 0.3f;
	color_rotatory_shot.life = 3000;
	color_rotatory_shot.anim.loop = true;

	animation = &idle_side;
	to_right = right;
	shot_timer = SDL_GetTicks();

	//explosion coordenates
	explosion.anim.PushBack({ 0, 247, 73, 64 });
	explosion.anim.PushBack({ 73, 247, 73, 64 });
	explosion.anim.PushBack({ 146, 247, 73, 64 });
	explosion.anim.PushBack({ 219, 247, 73, 64 });
	explosion.anim.PushBack({ 292, 247, 73, 64 });
	explosion.anim.PushBack({ 365, 247, 73, 64 });
	explosion.anim.PushBack({ 438, 247, 73, 64 });
	explosion.anim.PushBack({ 511, 247, 73, 64 });
	explosion.anim.PushBack({ 584, 247, 73, 64 });
	explosion.anim.PushBack({ 0, 0, 0, 0 });
	explosion.life = 1000;
	explosion.anim.speed = 0.2f;
	explosion.anim.loop = false;


	
}

void MegaTank::Move() {
	increment.y = (position.y - initial.y);
	increment.x = (position.x - initial.x);
	float distance_y =App->player->position.y -position.y ;
	if (!move_up) { // From the side
		if (!to_right) {//to left
			if (distance_y < 200) {
				animation = &sideward;
				position.x -= 0.8f;
				if (position.x < SCREEN_WIDTH / 2) {
					move_up = true;
					animation = &forward;
					start = SDL_GetTicks();
				}
			}			
		}
		else if (to_right) {//to right
			if (distance_y < 200) {
				animation = &sideward;
				position.x += 0.8f;
				if (position.x + 47 > SCREEN_WIDTH / 2) {
					move_up = true;
					animation = &forward;
					start = SDL_GetTicks();
				}
			}		
		}
	}
	else if (move_up) { // Going up			
		float speed=0.0f;
		if (SDL_GetTicks() - start < 1500) {
			speed = 1.0f;
		}
		else if (SDL_GetTicks() - start < 2000) {//STOP
			speed = 0.0f;
			animation = &idle_forward;
		}
		else if (SDL_GetTicks() - start < 3500) {
			speed = 1.0f;
			animation = &forward;
		}
		else if (SDL_GetTicks() - start < 4500) {//STOP
			speed = 0.0f;
			animation = &idle_forward;
		}
		position.y -= speed;
	}
	if (SDL_GetTicks() - shot_timer > 3000) {//Shoots every 3s
		ShotVector(color_rotatory_shot, { 2, 1 }, { position.x + 23, position.y + 24, });
		ShotVector(color_rotatory_shot, { -1, 1 }, { position.x + 23, position.y + 24 });
		ShotVector(color_rotatory_shot, { 3, 0 }, { position.x + 23, position.y + 24}, 300 );
		ShotVector(color_rotatory_shot, { -3, 0 }, { position.x + 23, position.y + 24},300 );
		ShotVector(color_rotatory_shot, { 1,-3 }, { position.x + 23, position.y + 24 },100);
		ShotVector(color_rotatory_shot, { -1, -3 }, { position.x + 23, position.y + 24 },100);
		ShotVector(color_rotatory_shot, { 3, -2 }, { position.x + 23, position.y + 24 },200);
		ShotVector(color_rotatory_shot, { -3, -2 }, { position.x + 23, position.y + 24 },200);

		shot_timer = SDL_GetTicks();
	}
	collider->SetPos(position.x, position.y);
}




void MegaTank::OnCollision(Collider*collider, int num_enemy) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		hits_life -= App->player->hit_dmg;
	}
	else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
		hits_life -= App->player2->hit_dmg;

	}
	if (hits_life <= 0) {
		App->player->score += score_points;
		App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);
	/*	fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_BigSpaceship_Explosion.wav");
		if (!fx_shoot) {
			LOG("Error loading shoot's fx: %s", Mix_GetError)
		}
		App->audio->Play_Fx(fx_shoot);*/
		delete App->enemies->enemies[num_enemy];
		App->enemies->enemies[num_enemy] = nullptr;

	}

}

void MegaTank::ShotVector(Particle& shot, iPoint velocity_vector, fPoint shot_initial_pos, uint delay) {

	shot.speed.x = velocity_vector.x;
	shot.speed.y = velocity_vector.y;
	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT, delay);

}

void MegaTank::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {}