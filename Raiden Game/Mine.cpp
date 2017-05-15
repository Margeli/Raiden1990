#include "Application.h"
#include "Mine.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


Mine::Mine(int x, int y, int shoot_num) : Enemy(x, y)
{
	
	sprite_path = App->textures->Load("Assets/Images/Mine.png");

	if (sprite_path == nullptr) {
		LOG("Error loading GreenShooter's textures. SDL Error: %s", SDL_GetError());
	}

	idle.PushBack({ 4,4,24,33 });
	idle.PushBack({ 28,4,24,33 });
	idle.PushBack({ 52,4,24,33 });
	idle.PushBack({ 28,4,24,33 });

	idle.speed = 0.3f;

	score_points = 180;//180
	hits_life = 4.0f;

	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	
	//Mine explosion shot
	color_rotatory_shot.anim.PushBack({ 22, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 39, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 56, 40, 6, 7 });//animation
	color_rotatory_shot.anim.speed = 0.3f;
	color_rotatory_shot.life = 3000;
	color_rotatory_shot.anim.loop = true;


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
}

void Mine::Move() {
	
		animation = &idle;
		if (App->player->position.x > position.x) {
			position.x += 0.3f;
		}
		else if (App->player->position.x < position.x) {		
			position.x -= 0.3f;
		}
		position.y += 0.1f;
	
}


void Mine::OnCollision(Collider*collider, int num_enemy) {
	
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		hits_life -= App->player->hit_dmg;
	}
	else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
		hits_life -= App->player2->hit_dmg;

	}
	if (hits_life <= 0) {
		ShotVector(color_rotatory_shot, { 2, 1 }, { position.x + 3, position.y + 3 });
		ShotVector(color_rotatory_shot, { -1, 1 }, { position.x + 3, position.y + 3 });
		ShotVector(color_rotatory_shot, { 3, 0 }, { position.x + 3, position.y + 3 });
		ShotVector(color_rotatory_shot, { -3, 0 }, { position.x + 3, position.y + 3 });
		ShotVector(color_rotatory_shot, { 1,-3 }, { position.x + 3, position.y + 3 });
		ShotVector(color_rotatory_shot, { -1, -3 }, { position.x + 3, position.y + 3 });
		ShotVector(color_rotatory_shot, { 3, -2 }, { position.x + 3, position.y + 3 });
		ShotVector(color_rotatory_shot, { -3, -2 }, { position.x + 3, position.y + 3 });
		App->player->score += score_points;
		App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);
		delete App->enemies->enemies[num_enemy];
		App->enemies->enemies[num_enemy] = nullptr;
		fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_SmallSpaceship_Explosion.wav");
		if (!fx_shoot) {
			LOG("Error loading shoot's fx: %s", Mix_GetError)
		}
	}

}

void Mine::ShotVector(Particle& shot, iPoint velocity_vector, fPoint shot_initial_pos) {

	shot.speed.x = velocity_vector.x;
	shot.speed.y = velocity_vector.y;
	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT);

}

void Mine::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {
}