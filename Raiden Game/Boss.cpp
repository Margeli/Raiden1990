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
	idle.speed = 0.01f;
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


	collider = App->collision->AddCollider({ 0, 0, 94, 81 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	App->enemies->AddEnemy(BOSS_CANNON, x+33 , y+28 , shoot_num);

}

void Boss::Move() {

	increment_y = (position.y - initial_y);
}




void Boss::OnCollision(Collider*collider, int num_enemy) {


}

void Boss::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}