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
	aim_down.PushBack({ 0,29,38,34 });
	aim_up.PushBack({ 38,29,38,34 });
	aim_right.PushBack({ 75,29,38,34 });
	aim_left.PushBack({ 113,29,38,34 });
	aim_down_left.PushBack({ 152,29,38,34 });
	aim_down_right.PushBack({ 190,29,38,34 });
	aim_up_right.PushBack({ 228,29,38,34 });
	aim_up_left.PushBack({ 266,29,38,34 });

	forward.PushBack({ 0,0,31,29 });
	side.PushBack({ 31,0,31,29 });
	forward_right.PushBack({ 62,0,31,29 });
	forward_left.PushBack({ 93,0,31,29 });

	sprite_path = App->textures->Load("Assets/Images/Tank.png");

	//GreenShooter Spaceship animations
	if (sprite_path == nullptr) {
		LOG("Error loading GreenShooter's textures. SDL Error: %s", SDL_GetError());
	}
	animation = &forward;

	shoot_number = shoot_num;
	initial_y = y;
	increment_y = 0.0f;


	score_points = 130;//130
	hits_aim = 2.0f;//2.0f
	hits_life = 3.0f;// 3.0f
	

	collider = App->collision->AddCollider({ 0, 0, 38, 34 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void Tank::Move() {

	increment_y = (position.y - initial_y);
	if (increment_y < 100) {
		if (App->player->position.x > position.x) {
			animation = &forward_left;
			position.x++;
			speed = 0.2f;
		}	
		else {
			animation = &forward_right;
			position.x--;
			speed = 0.2f;
		}
	}
	else {
		speed = -2.0f;
	}


	position.y += speed;
	collider->SetPos(position.x, position.y);
}




void Tank::OnCollision(Collider*collider, int num_enemy) {


}

void Tank::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}