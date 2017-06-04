#include "Application.h"
#include "Boss2.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


Boss2::Boss2(int x, int y, int shoot_num) : Enemy(x, y)
{

	sprite_path = App->textures->Load("Assets/Images/Boss2_lvl1.png");

	idle.PushBack({ 24,33,94,81 });
	idle.PushBack({ 24,149,94,81 });
	idle.PushBack({ 24,278,94,81 });
	idle.PushBack({ 24,395,94,81 });
	idle.speed = 0.01f;
	idle.loop = true;

	animation = &idle;

	score_points = 9660;
	hits_life = 155;


	//original_pos.x = x;
	//original_pos.y = y;

	collider = App->collision->AddCollider({ 0, 0, 94, 81 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	App->enemies->AddEnemy(BOSS_CANNON, x + 33, y + 28, shoot_num);
}

void Boss2::Move() {

	increment_y = (position.y - initial_y);
	
}

void Boss2::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}


void Boss2::OnCollision(Collider*collider, int num_enemy) {

	if (collider->type == COLLIDER_PLAYER_SHOT) {
		hits_life -= App->player->hit_dmg;
	}

	else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
		hits_life -= App->player2->hit_dmg;
	}

	else if (collider->type == COLLIDER_BOMB || collider->type == COLLIDER_BOMB2) {// FIX IF PLAYER 2 THROWS BOMB
		hits_life -= App->player->bomb_dmg;
	}

	if (hits_life <= 0) {
		Dead(collider, num_enemy);
	}
}
void Boss2::Dead(Collider* shooter, int num_enemy) {

	if (shooter->type == COLLIDER_PLAYER_SHOT || shooter->type == COLLIDER_BOMB) {
		App->player->score += score_points;
	}
	else if (shooter->type == COLLIDER_PLAYER2_SHOT || shooter->type == COLLIDER_BOMB2) {
		App->player2->score += score_points;
	}

	App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);
	
	fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_Boss_Explosion.wav");
	if (!fx_shoot) {
		LOG("Error loading shoot's fx: %s", Mix_GetError)
	}
	App->audio->Play_Fx(fx_shoot);
	delete App->enemies->enemies[num_enemy];
	App->enemies->enemies[num_enemy] = nullptr;

}

