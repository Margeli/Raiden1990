#include "Application.h"
#include "StaticCannon.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"


StaticCannon::StaticCannon(int x, int y, int shoot_num) : Enemy(x, y)
{
	sprite_path = App->textures->Load("Assets/Images/Static_Cannon.png");
	graphics = App->textures->Load("Assets/Images/Static_Cannon.png");//Used to put the base behind the animation
	if (graphics == nullptr) {
		LOG("Error loading StaticCannon base texture %s", SDL_GetError);		
	}
	
	//GreenShooter Spaceship animations
	if (sprite_path == nullptr) {
		LOG("Error loading Static Cannon's textures. SDL Error: %s", SDL_GetError());
	}

	//Static Cannon shot
	color_rotatory_shot.anim.PushBack({ 22, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 39, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 56, 40, 6, 7 });
	color_rotatory_shot.anim.speed = 0.3f;
	color_rotatory_shot.life = 3000;
	color_rotatory_shot.anim.loop = true;

	

	base={ 0,0,28,25 };
	
	down.PushBack({ 0,26,26,22 });
	up.PushBack({ 26,26,26,22 });
	right.PushBack({ 52,26,26,22 });
	left.PushBack({ 78,26,26,22 });
	up_left.PushBack({ 104,26,26,22 });
	up_right.PushBack({ 130,26,26,22 });
	down_right.PushBack({ 156,26,26,22 });
	down_left.PushBack({ 182,26,26,22 });

	animation = &down;

	//explosion animation
	explosion.anim.PushBack({ 0, 0, 32, 30 });
	explosion.anim.PushBack({ 32, 0, 32, 30 });
	explosion.anim.PushBack({ 64, 0, 32, 30 });
	explosion.anim.PushBack({ 96, 0, 32, 30 });
	explosion.anim.PushBack({ 128, 0, 32, 30 });
	explosion.anim.PushBack({ 160, 0, 32, 30 });
	explosion.anim.PushBack({ 192, 0, 32, 30 });
	explosion.anim.PushBack({ 224, 0, 32, 30 });
	explosion.anim.PushBack({ 256, 0, 32, 30 });
	explosion.anim.PushBack({ 288, 0, 32, 30 });
	explosion.anim.PushBack({ 320, 0, 32, 30 });
	explosion.anim.PushBack({ 0, 0, 0, 0 });
    explosion.life = 1000;
	explosion.anim.speed = 0.2f;
	explosion.anim.loop = false;

	//destroyed base
	destroyed_base.anim.PushBack({ 566, 0, 32, 30 });
	destroyed_base.life = 5000;
	//shoot_number = shoot_num;
	

	score_points = 120;//120
	hits_life = 4.0f;// 4.0f
	

	collider = App->collision->AddCollider({ x, y, 28, 25 }, COLLIDER_TYPE::COLLIDER_BOX, (Module*)App->enemies); // collider type box because the tank is in the ground, so there is no damage for touching with the player's collider

	timer_shot = SDL_GetTicks();

}

void StaticCannon::Move() {
	
	if ((App->player->position.y > position.y+25)) {// DOWN
		
		if ((App->player->position.x > position.x) && (App->player->position.x < position.x + 28)) {
			animation = &down;
		}
		else if (App->player->position.x > position.x) {
			animation = &down_right;
		}
		else if (App->player->position.x < position.x+28) {
			animation = &down_left;
		}
	}
	else if ((App->player->position.y < position.y)) {//UP

		if ((App->player->position.x > position.x) && (App->player->position.x < position.x + 28)) {
			animation = &up;
		}
		else if (App->player->position.x > position.x) {
			animation = &up_right;
		}
		else if (App->player->position.x < position.x + 28) {
			animation = &up_left;
		}
	}
	else if ((App->player->position.y > position.y ) && (App->player->position.y < position.y+ 25)) {//MIDDLE
		if (App->player->position.x > position.x) {
			animation = &right;
		}
		else if (App->player->position.x < position.x + 28) {
			animation = &left;
		}
	}

	if (SDL_GetTicks() - timer_shot > 2500) {
		Shot(color_rotatory_shot, App->player->position, position);
			timer_shot = SDL_GetTicks();
	}



	App->render->Blit(graphics, position.x, position.y, &base);//Draws the base of the Cannon
	
}




void StaticCannon::OnCollision(Collider*collider, int num_enemy) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		hits_life -= App->player->hit_dmg;
	}
	else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
		hits_life -= App->player2->hit_dmg;

	}
	if (hits_life <= 0) {
		App->player->score += score_points;
		App->particles->AddParticle(destroyed_base, position.x - 1.25, position.y - 2.25, COLLIDER_EXPLOSION);
		App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);
 		fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_StaticCannon_Explosion.wav");
		if (!fx_shoot) {
			LOG("Error loading shoot's fx: %s", Mix_GetError)
		}
		App->audio->Play_Fx(fx_shoot);
		delete App->enemies->enemies[num_enemy];
		App->enemies->enemies[num_enemy] = nullptr;
		App->textures->Unload(graphics);// NEED TO PUT IN THE PARTICLE SPRITESHEET THE BASE OF THE CANNON, 

	}


}

void StaticCannon::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {
	shot.speed = { 0,0 };
	
	if (animation == &up) {
		shot.speed = { 0,-5 };
	}
	else if (animation == &down) {
		shot.speed = { 0,3 };
	}
	else if (animation == &right) {
		shot.speed = { 3,0 };

	}
	else if (animation == &left) {
		shot.speed = { -3,0 };
	}
	else if (animation == &down_right) {
		shot.speed = { 3,3 };

	}
	else if (animation == &down_left) {
		shot.speed = { -3,3 };
	}
	else if (animation == &up_right) {
		shot.speed = { 3,-4 };

	}
	else if (animation == &up_left) {
		shot.speed = { -3,-4};
	}

	App->particles->AddParticle(shot, shot_initial_pos.x+12, shot_initial_pos.y+13, COLLIDER_ENEMY_SHOT);

}