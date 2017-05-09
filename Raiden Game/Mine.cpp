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

	idle.speed = 1.0f;
}

void Mine::Move() {
	
	increment_y = (position.y - initial_y);
}




void Mine::OnCollision(Collider*collider, int num_enemy) {
	

}

void Mine::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {


}