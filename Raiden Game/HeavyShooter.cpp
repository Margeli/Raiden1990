#include "Application.h"
#include "HeavyShooter.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


HeavyShooter::HeavyShooter(int x, int y, int shoot_num) : Enemy(x, y)
{

}

void HeavyShooter::Move() {

	increment_y = (position.y - initial_y);
}




void HeavyShooter::OnCollision(Collider*collider, int num_enemy) {


}

void HeavyShooter::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}