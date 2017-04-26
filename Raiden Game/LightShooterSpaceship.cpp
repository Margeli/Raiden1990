#include "Application.h"
#include "LightShooterSpaceship.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


LightShooter_Spaceship::LightShooter_Spaceship(int x, int y, int count) : Enemy(x, y)
{

	//explosion  particle animation (2nd row particle spritesheet.)
	explosion.anim.PushBack({ 2,60,34,30 });
	explosion.anim.PushBack({ 36 ,60,34,30 });
	explosion.anim.PushBack({ 70,60,34,30 });
	explosion.anim.PushBack({ 104 ,60,34,30 });
	explosion.anim.PushBack({ 138 ,60,34,30 });
	explosion.anim.PushBack({ 172 ,60,34,30 });
	explosion.anim.PushBack({ 206 ,60,34,30 });
	explosion.anim.PushBack({ 240,60,34,30 });
	explosion.anim.PushBack({ 274,60,34,30 });
	explosion.anim.PushBack({ 308 ,60,34,30 });
	explosion.anim.PushBack({ 342,60,34,30 });
	explosion.anim.PushBack({ 376 ,60,34,30 });
	explosion.anim.PushBack({ 410,60,34,30 });
	explosion.anim.PushBack({ 446 ,60,34,30 });
	explosion.anim.PushBack({ 478 ,60,34,30 });
	explosion.anim.PushBack({ 512,60,34,30 });
	explosion.anim.PushBack({ 0,0,0,0 });

	explosion.life = 1000;
	explosion.anim.loop = false;

	sprite_path = App->textures->Load("Assets/Images/Light_Shooter.png");

	//LightShooter Spaceship animations
	if (sprite_path == nullptr) {
		LOG("Error loading LightShooter's textures. SDL Error: %s", SDL_GetError());
	}



	//Animation from facing downwards to facing right

	down.PushBack({ 1,1,30,30 }); //Facing down
	down_right.PushBack({ 25,1,30,30 });
	down_right.PushBack({ 53,1,30,30 });
	down_right.PushBack({ 81,1,30,30 });
	down_right.speed = 0.05f;

	downwards_right.PushBack({ 25,1,30,30 });

	//Animation from right to up

	right.PushBack({ 114,1,30,30 }); //Facing right
	right_up.PushBack({ 147,1,30,30 });
	right_up.PushBack({ 182,1,30,30 });
	right_up.PushBack({ 212,1,30,30 });
	right_up.speed = 0.05f;



	//Animation from up to left

	up.PushBack({ 241,1,30,30 }); //Facing up
	up_left.PushBack({ 266,1,30,30 });
	up_left.PushBack({ 294,1,30,30 });
	up_left.PushBack({ 322,1,30,30 });
	up_left.speed = 0.01f;



	//Animation from left to down

	left.PushBack({ 356,1,31,29 }); //Facing left
	left_down.PushBack({ 392,1,30,30 });
	left_down.PushBack({ 426,1,30,30 });
	left_down.PushBack({ 458,1,30,30 });
	left_down.speed = 0.01f;


	left_downwards.PushBack({ 458,1,30,30 });

	score_points = 130;
	hits_life = 1.0f;
	
	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	if (position.x < App->player->position.x) {
		path.PushBack({ 0.0f, +0.8f }, 1, &left_downwards);
		}
	else if (position.x > App->player->position.x) {
		path.PushBack({ 0.0f, +0.8f }, 1, &downwards_right);
		}

	else if (position.y >= App->player->position.y-20) {
		downwards = false;
		position.y--;
		path.PushBack({ 0.0f, -0.8f }, 1, &up);
	}
	
	original_pos.x = x;
	original_pos.y = y;
}

void LightShooter_Spaceship::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
}

void LightShooter_Spaceship::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {
	if (position.y == -1500) {
		App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT);
	}
	
}

void LightShooter_Spaceship::OnCollision(Collider*collider, int num_enemy) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		hits_life -= App->player->hit_dmg;
	}
	else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
		hits_life -= App->player2->hit_dmg;

	}
	if (hits_life <= 0) {
		App->player->score += score_points;
		App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);
		fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_SmallSpaceship_Explosion.wav");
		if (!fx_shoot) {
			LOG("Error loading shoot's fx: %s", Mix_GetError)
		}
		App->audio->Play_Fx(fx_shoot);
		delete App->enemies->enemies[num_enemy];
		App->enemies->enemies[num_enemy] = nullptr;

	}
}