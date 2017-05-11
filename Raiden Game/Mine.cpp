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

	sprite_path = App->textures->Load("Assets/Images/Bomb.png");

	if (sprite_path == nullptr) {
		LOG("Error loading GreenShooter's textures. SDL Error: %s", SDL_GetError());
	}

	idle.PushBack({ 73,5,24,34 });
	idle.PushBack({ 100,5,16,34 });
	idle.PushBack({ 120,5,16,34 });
	idle.PushBack({ 100,5,16,34 });

	idle.speed = 0.3f;

	score_points = 180;//180
	hits_life = 4.0f;

	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Mine::Move() {
	if (downwards) {
		animation = &idle;
		if (App->player->position.x > position.x) {
			b_left = false;
			b_right = true;
			position.x += 0.3f;
		}
		else if (App->player->position.x < position.x) {
			b_left = true;
			b_right = false;
			position.x -= 0.3f;
		}
		position.y += 0.1f;
	}
}


void Mine::OnCollision(Collider*collider, int num_enemy) {
	
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		hits_life -= App->player->hit_dmg;
	}
	else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
		hits_life -= App->player2->hit_dmg;

	}
	if (hits_life <= 0) {
		App->player->score += score_points;
		App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);
		delete App->enemies->enemies[num_enemy];
		App->enemies->enemies[num_enemy] = nullptr;

	}

}

void Mine::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}