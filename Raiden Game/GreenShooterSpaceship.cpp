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

	idle.PushBack({ 243, 48,71,65 });//no-turbo 

	boost.PushBack({165,48,64,65 });
	boost.PushBack({ 87,48,64,65 });
	boost.PushBack({ 9,48,64,65 });

	backward_idle.PushBack({ 318,114,64,65 });//no-turbo backwards

	backward_boost.PushBack({ 165,114,64,65 });
	backward_boost.PushBack({ 87,114,64,65 });
	backward_boost.PushBack({ 9,114,64,65 });
	
	animation = &idle;

}

void GreenShooter_Spaceship::Move() {

	
}

void GreenShooter_Spaceship::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {

}