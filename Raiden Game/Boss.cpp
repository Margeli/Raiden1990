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

	App->enemies->AddEnemy(BOSS_CANNON, x+33 , y+28 , shoot_num);
}

void Boss::Move() {

	increment_y = (position.y - initial_y);
}




void Boss::OnCollision(Collider*collider, int num_enemy) {


}

void Boss::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}