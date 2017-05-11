#include "Application.h"
#include "Boss.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


Boss::Boss(int x, int y, int shoot_num) : Enemy(x, y)
{

}

void Boss::Move() {

	increment_y = (position.y - initial_y);
}




void Boss::OnCollision(Collider*collider, int num_enemy) {


}

void Boss::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}