#include "Application.h"
#include "Tank.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


Tank::Tank(int x, int y, int shoot_num) : Enemy(x, y)
{
	
}

void Tank::Move() {

	increment_y = (position.y - initial_y);
}




void Tank::OnCollision(Collider*collider, int num_enemy) {


}

void Tank::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}