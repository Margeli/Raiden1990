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

	forward.PushBack({ 0,0,31,29 });
	side.PushBack({ 31,0,31,29 });
	forward_right.PushBack({ 62,0,31,29 });
	forward_left.PushBack({ 93,0,31,29 });

	explosion.anim.PushBack({ 0,0,32,30 });
	explosion.anim.PushBack({ 32,0,32,30 });
	explosion.anim.PushBack({ 64,0,32,30 });
	explosion.anim.PushBack({ 96,0,32,30 });
	explosion.anim.PushBack({ 128,0,32,30 });
	explosion.anim.PushBack({ 160,0,32,30 });
	explosion.anim.PushBack({ 192,0,32,30 });
	explosion.anim.PushBack({ 224,0,32,30 });
	explosion.anim.PushBack({ 256,0,32,30 });
	explosion.anim.PushBack({ 288,0,32,30 });
	explosion.anim.PushBack({ 320,0,32,30 });
	explosion.anim.speed = 0.2f;
	explosion.anim.loop = false;
	explosion.life = 10000;// the explosion remains in the ground, so it lasts 10s



	sprite_path = App->textures->Load("Assets/Images/Tank.png");

	
	if (sprite_path == nullptr) {
		LOG("Error loading Tank's textures. SDL Error: %s", SDL_GetError());
	}
	animation = &forward;

	shoot_number = shoot_num;
	initial_y = y;
	increment_y = 0.0f;


	score_points = 130;//130
	
	hits_life = 1.0f;// 1.0f
	player_initial_x = App->player->position.x; //Stores player position X when tank is spawning.

	collider = App->collision->AddCollider({ 0, 0, 30, 27 }, COLLIDER_TYPE::COLLIDER_BOX, (Module*)App->enemies);//collider type box because the tank is in the ground, so there is no damage for touching with the player's collider 

	App->enemies->AddEnemy(CANNON_TANK, x-4, y-2, shoot_num);

}

void Tank::Move() {

	increment_y = (position.y - initial_y);

	if (player_initial_x > position.x) {
		animation = &forward_left;
		position.x++;
		speed = 0.1f;

	}
	else if (player_initial_x< position.x) {
		animation = &forward_right;
		position.x--;
		speed = 0.1f;
	}
	else {
		speed = 0.0f;
		animation = &side;




	}
	position.y += speed;
	collider->SetPos(position.x+1, position.y-1);// moved because we want the cannon of the tank is shot first
}




void Tank::OnCollision(Collider*collider, int num_enemy) {
	
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

void Tank::Dead(Collider* shooter, int num_enemy) {

	if (shooter->type == COLLIDER_PLAYER_SHOT || shooter->type == COLLIDER_BOMB) {
		App->player->score += score_points;
	}
	else if (shooter->type == COLLIDER_PLAYER2_SHOT || shooter->type == COLLIDER_BOMB2) {
		App->player2->score += score_points;
	}

	App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);
	fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_Tank_Explosion.wav");
	if (!fx_shoot) {
		LOG("Error loading shoot's fx: %s", Mix_GetError)
	}
	App->audio->Play_Fx(fx_shoot);
	delete App->enemies->enemies[num_enemy];
	App->enemies->enemies[num_enemy] = nullptr;


}

void Tank::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}