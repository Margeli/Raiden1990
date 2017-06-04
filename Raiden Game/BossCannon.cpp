#include "Application.h"
#include "BossCannon.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"


BossCannon::BossCannon(int x, int y, int shoot_num) : Enemy(x, y)
{
	down.PushBack({ 129,64,28,25 });

	up.PushBack({ 129,33,28,25 });

	right.PushBack({ 219,33,28,25 });

	left.PushBack({ 219,64,28,25 });

	down_left.PushBack({ 159,64,28,25 });
	down_left.PushBack({ 189,64,28,25 });
	down_left.PushBack({ 219,64,28,25 });
	down_left.speed = 0.1f;

	down_right.PushBack({ 279,33,28,25 });
	down_right.PushBack({ 309,33,28,25 });
	down_right.PushBack({ 339,33,28,25 });
	down_right.speed = 0.1f;

	up_right.PushBack({ 159,33,28,25 });
	up_right.PushBack({ 189,33,28,25 });
	up_right.PushBack({ 219,33,28,25 });
	up_right.speed = 0.1f;

	up_left.PushBack({ 279,64,28,25 });
	up_left.PushBack({ 309,64,28,25 });
	up_left.PushBack({ 339,64,28,25 });
	up_left.speed = 0.1f;

	

	sprite_path = App->textures->Load("Assets/Images/Boss_lvl1.png");


	if (sprite_path == nullptr) {
		LOG("Error loading BossCannon's textures. SDL Error: %s", SDL_GetError());
	}
	
	

	collider = App->collision->AddCollider({ 0, 0, 28, 25 }, COLLIDER_TYPE::COLLIDER_TURRET, (Module*)App->enemies);//JUST FOR DECORATION

	

}

void BossCannon::Move() {


	//SAME MOVEMENT AS THE TANK
	if (position.x + 33 > 100) {//right
		position.x--;

			//SAME MOVEMENT AS THE BOSS
			

			if ((App->player->position.y - 2 > position.y + 34)) {// DOWN

				if ((App->player->position.x > position.x) && (App->player->position.x < position.x + 38)) {
					animation = &down;
				}
				else if (App->player->position.x > position.x - 2) {
					animation = &down_right;
				}
				else if (App->player->position.x < position.x + 38) {
					animation = &down_left;
				}
			}
			else if ((App->player->position.y < position.y)) {//UP

				if ((App->player->position.x > position.x) && (App->player->position.x < position.x + 38)) {
					animation = &up;
				}
				else if (App->player->position.x > position.x) {
					animation = &up_right;
				}
				else if (App->player->position.x < position.x + 38) {
					animation = &up_left;
				}
			}
			else if ((App->player->position.y > position.y) && (App->player->position.y < position.y + 34)) {//MIDDLE
				if (App->player->position.x > position.x) {
					animation = &right;
				}
				else if (App->player->position.x < position.x + 38) {
					animation = &left;
				}
			}


			//position.y += -0.8f;
			collider->SetPos(position.x, position.y);

	}
}




void BossCannon::OnCollision(Collider*collider, int num_enemy) {

	if (collider->type == COLLIDER_EXPLOSION) {		
		delete App->enemies->enemies[num_enemy];
		App->enemies->enemies[num_enemy] = nullptr;

	}
	
}

void BossCannon::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {
	
}