#include "Application.h"
#include "HeavyShooter.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

HeavyShooter::HeavyShooter(int x, int y, int shoot_num) : Enemy(x, y)
{
	sprite_path = App->textures->Load("Assets/Images/Heavy_Shooter.png");

	//HeavyShooter Spaceship animations
	if (sprite_path == nullptr) {
		LOG("Error loading GreenShooter's textures. SDL Error: %s", SDL_GetError());
	}
	idle.PushBack({0,0,48,44});
	idle.PushBack({ 48,0,48,44 });
	shoot.PushBack({96,0,48,44 });
	shoot.PushBack({ 144,0,48,44 });
	shoot.PushBack({ 192,0,48,44 });
	shoot.PushBack({ 240,0,48,44 });
	shoot.PushBack({ 288,0,48,44 });
	shoot.PushBack({ 336,0,48,44 });
	shoot.speed = 0.5f;
	idle.speed = 0.5f;
	animation = &idle;

	shoot_number = shoot_num;
	initial_y = y;
	increment_y = 0.0f;


	score_points = 480;//480
	hits_life = 30.0f;// 30.0f
	move_loop = 0;
	start_move_loop = 0;

	collider = App->collision->AddCollider({ 0, 0,48, 44 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	
}

void HeavyShooter::Move() {

	increment_y = (position.y - initial_y); // idle movement position
	
	if (increment_y < 25&&first) {
		speed = 0.3f;
		
	}
	
	else if (move_loop == 0) {
		start_move_loop = SDL_GetTicks();
		speed = -1.0f;
		first = false;
		
		if (position.x+24 > App->player->position.x) //right
			right = true;		
		else  // left
			right = false;		
		move_loop = 1;//starts movement loop
	}
	else 
		move_loop = SDL_GetTicks() - start_move_loop;

	if (move_loop > 1500&&move_loop<3000) {
		speed = 0.3f;
		if (right)
			position.x--;
		else
			position.x++;
	}
	else if (move_loop > 3000&&move_loop<3500) {
		speed = -1.0f;
	}
	else if (move_loop > 3500&& move_loop < 5450) {
		speed = -2.0f;
		if (right)
			position.x++;
		else
			position.x--;	
	}
	else if (move_loop > 5450) {
		speed = -1.0f;
		move_loop = 0;//starts the loop again
		start_move_loop = 0;
	}
	position.y += speed;
	collider->SetPos(position.x, position.y);
}




void HeavyShooter::OnCollision(Collider*collider, int num_enemy) {


}

void HeavyShooter::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}