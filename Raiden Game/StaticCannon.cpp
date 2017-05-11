#include "Application.h"
#include "StaticCannon.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


StaticCannon::StaticCannon(int x, int y, int shoot_num) : Enemy(x, y)
{

}

void StaticCannon::Move() {

	increment_y = (position.y - initial_y);
}




void StaticCannon::OnCollision(Collider*collider, int num_enemy) {


}

void StaticCannon::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}