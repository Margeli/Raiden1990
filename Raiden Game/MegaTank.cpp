#include "Application.h"
#include "MegaTank.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


MegaTank::MegaTank(int x, int y, int shoot_num) : Enemy(x, y)
{

}

void MegaTank::Move() {

	increment_y = (position.y - initial_y);
}




void MegaTank::OnCollision(Collider*collider, int num_enemy) {


}

void MegaTank::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}