#include "Application.h"
#include "Boss.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


Boss::Boss(int x, int y, int shoot_num) : Enemy(x, y)
{

	sprite_path = App->textures->Load("Assets/Images/Boss_lvl1.png");

	idle.PushBack({ 24,33,94,81 });
	idle.PushBack({ 24,149,94,81 });
	idle.PushBack({ 24,278,94,81 });
	idle.PushBack({ 24,395,94,81 });
	idle.speed = 0.05f;
	idle.loop = true;

	animation = &idle;



	//Boss shots
	bouncing_shot.anim.PushBack({ 511, 172, 6, 7 });
	bouncing_shot.anim.PushBack({ 526, 172, 6, 7 });	
	bouncing_shot.anim.speed = 0.3f;
	bouncing_shot.life = 3000;
	bouncing_shot.anim.loop = true;

	color_rotatory_shot.anim.PushBack({ 22, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 39, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 56, 40, 6, 7 });
	color_rotatory_shot.anim.speed = 0.3f;
	color_rotatory_shot.life = 3000;
	color_rotatory_shot.anim.loop = true;

	star_shot.anim.PushBack({ 458, 172, 9, 7 });
	star_shot.anim.PushBack({ 475, 172, 9, 7 });
	star_shot.anim.PushBack({ 492, 172, 9, 7 });
	star_shot.anim.speed = 0.3f;
	star_shot.life = 3000;
	star_shot.anim.loop = true;

	score_points = 9660;
	hits_life = 155;

	collider = App->collision->AddCollider({ 0, 0, 94, 81 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	App->enemies->AddEnemy(BOSS_CANNON, x+33 , y+28 , shoot_num);

}

void Boss::Move() {

	increment_y = (position.y - initial_y);
}




void Boss::OnCollision(Collider*collider, int num_enemy) {

	if (collider->type == COLLIDER_PLAYER_SHOT) {
		hits_life -= App->player->hit_dmg;
	}

	else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
		hits_life -= App->player2->hit_dmg;
	}

	else if (collider->type == COLLIDER_BOMB || collider->type == COLLIDER_BOMB2) {// FIX IF PLAYER 2 THROWS BOMB
		hits_life -= App->player->bomb_dmg;
	}

	if (hits_life <= 0) {
		Dead(collider, num_enemy);
	}

}

void Boss::Dead(Collider* shooter, int num_enemy) {

	if (shooter->type == COLLIDER_PLAYER_SHOT || shooter->type == COLLIDER_BOMB) {
		App->player->score += score_points;
	}
	else if (shooter->type == COLLIDER_PLAYER2_SHOT || shooter->type == COLLIDER_BOMB2) {
		App->player2->score += score_points;
	}

	App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);

	fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_Boss_Explosion.wav");
	if (!fx_shoot) {
		LOG("Error loading shoot's fx: %s", Mix_GetError)
	}
	App->audio->Play_Fx(fx_shoot);
	delete App->enemies->enemies[num_enemy];
	App->enemies->enemies[num_enemy] = nullptr;

}

void Boss::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}

void Boss::ShotVector(Particle& shot, iPoint velocity_vector, fPoint shot_initial_pos) {

	shot.speed.x = velocity_vector.x;
	shot.speed.y = velocity_vector.y;
	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT);

}