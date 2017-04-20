#include "Application.h"
#include "GreenShooterSpaceship.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"


GreenShooter_Spaceship::GreenShooter_Spaceship(int x, int y, int count) : Enemy(x, y)
{
	sprite_path = App->textures->Load("Assets/Images/Green_Shooter.png");

	//GreenShooter Spaceship animations
	if (sprite_path == nullptr) {
		LOG("Error loading GreenShooter's textures. SDL Error: %s", SDL_GetError());
	}

	idle.PushBack({ 243, 48,71,53 });//no-turbo 

	boost.PushBack({165,48,71,53 });
	boost.PushBack({ 87,48,71,53 });
	boost.PushBack({ 9,48,71,53 });
	boost.speed = 0.5f;

	backward_idle.PushBack({ 243,114,71,53 });//no-turbo backwards

	backward_boost.PushBack({ 165,114,71,53 });
	backward_boost.PushBack({ 87,114,71,53 });
	backward_boost.PushBack({ 9,114,71,53 });
	backward_boost.speed = 0.5f;

	animation = &idle;

	initial_y = y;
	increment_y = 0.0f;

	down = true;
	
	collider = App->collision->AddCollider({ 0, 0, 71, 53 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void GreenShooter_Spaceship::Move() {
	increment_y = (position.y - initial_y);

	if (shooting) {	
		
		
		
		shooting = false;
	}
	if (down) {
		if (increment_y < 55)
			speed = 0.3f;

		else if (increment_y > 55 && increment_y < 120) {
			speed = 1.0f;
			animation = &boost;
			if (position.x < App->player->position.x)position.x++;
			else if (position.x > App->player->position.x)position.x--;
		}

		else if (increment_y >= 120) {
			down = false;
			speed = -2.0f;
			animation = &backward_idle;
		}
	}
	else
	{
		if (increment_y < 120&&increment_y>-200) {
			speed = -2.3f;
		}
		else if (increment_y < -200) {
			speed = -3.0f;
			animation = &backward_boost;
		}
	}
	position.y += speed;
	
}

void GreenShooter_Spaceship::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {

}