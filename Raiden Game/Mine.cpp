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
	//Mine explosion shot
	color_rotatory_shot.anim.PushBack({ 22, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 39, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 56, 40, 6, 7 });//animation
	color_rotatory_shot.anim.speed = 0.3f;

	color_rotatory_shot.life = 3000;
	color_rotatory_shot.anim.loop = true;
}

void Mine::Move() {
	

}




void Mine::OnCollision(Collider*collider, int num_enemy) {
	

}