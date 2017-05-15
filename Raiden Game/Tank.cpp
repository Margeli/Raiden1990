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


	if (hits_life <= 0) {
		App->player->score += score_points;
		App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);
		fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_Tank_Explosion.wav");
		if (!fx_shoot) {
			LOG("Error loading shoot's fx: %s", Mix_GetError)
		}
		App->audio->Play_Fx(fx_shoot);
		delete App->enemies->enemies[num_enemy];
		App->enemies->enemies[num_enemy] = nullptr;

	}

}

void Tank::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}