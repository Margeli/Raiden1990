#include "Application.h"
#include "Boss.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel1.h"
#include "ModuleStageCompleted.h"


#include "SDL/include/SDL_timer.h"

Boss::Boss(int x, int y, int shoot_num) : Enemy(x, y)
{

	sprite_path = App->textures->Load("Assets/Images/Boss_lvl1.png");

	idle.PushBack({ 24,33,94,81 });
	idle.PushBack({ 24,149,94,81 });
	idle.PushBack({ 24,278,94,81 });
	idle.PushBack({ 24,395,94,81 });
	idle.speed = 0.05f;
	idle.loop = true;

	animation = &idle;

	//Boss shots
	bouncing_shot.anim.PushBack({ 511, 172, 6, 7 });
	bouncing_shot.anim.PushBack({ 526, 172, 6, 7 });	
	bouncing_shot.anim.speed = 0.3f;
	bouncing_shot.life = 3000;
	bouncing_shot.anim.loop = true;

	color_rotatory_shot.anim.PushBack({ 22, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 39, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 56, 40, 6, 7 });
	color_rotatory_shot.anim.speed = 0.3f;
	color_rotatory_shot.life = 3000;
	color_rotatory_shot.anim.loop = true;

	star_shot.anim.PushBack({ 458, 172, 10, 8 });
	star_shot.anim.PushBack({ 475, 172, 10, 8 });
	star_shot.anim.PushBack({ 492, 172, 10, 8 });
	star_shot.anim.speed = 0.2f;
	star_shot.life = 3000;
	star_shot.anim.loop = true;

	explosion.anim.PushBack({ 0, 247, 73, 64 });
	explosion.anim.PushBack({ 73, 247, 73, 64 });
	explosion.anim.PushBack({ 146, 247, 73, 64 });
	explosion.anim.PushBack({ 219, 247, 73, 64 });
	explosion.anim.PushBack({ 292, 247, 73, 64 });
	explosion.anim.PushBack({ 365, 247, 73, 64 });
	explosion.anim.PushBack({ 438, 247, 73, 64 });
	explosion.anim.PushBack({ 511, 247, 73, 64 });
	explosion.anim.PushBack({ 584, 247, 73, 64 });
	explosion.anim.PushBack({ 0, 0, 0, 0 });
	explosion.life = 1000;
	explosion.anim.speed = 0.2f;
	explosion.anim.loop = false;

	score_points = 9660;
	hits_life = 155.0f;

	initial_y = y;

	collider = App->collision->AddCollider({ 0, 0, 94, 81 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	App->enemies->AddEnemy(BOSS_CANNON, x+34 , y+28 , shoot_num);
	born = SDL_GetTicks();
}

void Boss::Move() {
	
	increment_y = -(position.y - initial_y);

	if (shot_vector) {
		ShotVector(bouncing_shot, { 2,0 }, {position.x+71, position.y+34}); //right
		ShotVector(bouncing_shot, { -2,0 }, { position.x+23, position.y+34 });//left
		ShotVector(bouncing_shot, { 2,2 }, { position.x+68, position.y+54 });//down right
		ShotVector(bouncing_shot, { -2,2 }, { position.x+23, position.y+54 });//down left
		shot_vector = false;
	}
	if (burst_shot) {
		ShotVector(color_rotatory_shot, { 1,2 }, { position.x + 47, position.y + 41 }); //left
		ShotVector(color_rotatory_shot, { -1,2 }, { position.x + 47, position.y + 41 }); //right
		ShotVector(color_rotatory_shot, { 2,2 }, { position.x + 47, position.y + 41 }); //left down
		ShotVector(color_rotatory_shot, { -2,2 }, { position.x + 47, position.y + 41 }); //right down
		ShotVector(star_shot, { 0,2 }, { position.x + 47, position.y + 41 }); //star shot burst
		ShotVector(star_shot, { 0,2 }, { position.x + 47, position.y + 41 }, 80);//  |
		ShotVector(star_shot, { 0,2 }, { position.x + 47, position.y + 41 }, 160);// V
		ShotVector(star_shot, { 0,2 }, { position.x + 47, position.y + 41 }, 240);
		ShotVector(star_shot, { 0,2 }, { position.x + 47, position.y + 41 }, 320);
		burst_shot = false;
	}
	if (SDL_GetTicks() - born > 5000) {//5s without shooting
		if (shot_timer == 0) {
			shot_timer = SDL_GetTicks();
		}
		else if (SDL_GetTicks() - shot_timer > 2000) {//shots every 2 s
			shot_vector = true;
			shot_timer = 0;
		}
		if (star_shot_timer == 0) {
			star_shot_timer = SDL_GetTicks();
		}
		else if (SDL_GetTicks() - star_shot_timer > 10000) {//shots every 10s
			burst_shot = true;
			star_shot_timer = 0;		
		}
	}

	if (position.x + 33 > 100) {//right
		position.x--;
	}

	collider->SetPos(position.x, position.y);

}




void Boss::OnCollision(Collider*collider, int num_enemy) {

	if (collider->type == COLLIDER_PLAYER_SHOT) {
		hits_life -= App->player->hit_dmg;
	}

	else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
		hits_life -= App->player2->hit_dmg;
	}

	else if (collider->type == COLLIDER_BOMB || collider->type == COLLIDER_BOMB2) {
		hits_life -= App->player->bomb_dmg;
	}

	if (hits_life <= 0) {
		Dead(collider, num_enemy);
	}

}

void Boss::Dead(Collider* shooter, int num_enemy) {

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
	
	App->fade->FadeToBlack(App->level1, App->stageCompleted);


}

void Boss::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}

void Boss::ShotVector(Particle& shot, iPoint velocity_vector, fPoint shot_initial_pos, unsigned int delay) {

	shot.speed.x = velocity_vector.x;
	shot.speed.y = velocity_vector.y;
	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT, delay);

}