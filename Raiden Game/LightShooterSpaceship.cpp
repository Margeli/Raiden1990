#include "Application.h"
#include "GreenShooterSpaceship.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"


LightShooter_Spaceship::LightShooter_Spaceship(int x, int y, int count) : Enemy(x, y)
{

	//explosion  particle animation (2nd row particle spritesheet.)
	explosion.anim.PushBack({2,60,34,30});
	explosion.anim.PushBack({36 ,60,34,30 });
	explosion.anim.PushBack({ 70,60,34,30 });
	explosion.anim.PushBack({104 ,60,34,30 });
	explosion.anim.PushBack({138 ,60,34,30 }); 
	explosion.anim.PushBack({172 ,60,34,30 });
	explosion.anim.PushBack({206 ,60,34,30 });
	explosion.anim.PushBack({ 240,60,34,30 });
	explosion.anim.PushBack({ 274,60,34,30 });
	explosion.anim.PushBack({308 ,60,34,30 });
	explosion.anim.PushBack({ 342,60,34,30 });
	explosion.anim.PushBack({376 ,60,34,30 });
	explosion.anim.PushBack({ 410,60,34,30 });
	explosion.anim.PushBack({446 ,60,34,30 });
	explosion.anim.PushBack({478 ,60,34,30 });
	explosion.anim.PushBack({ 512,60,34,30 });
	
	sprite_path = App->textures->Load("Assets/Images/Light_Shooter.png");

	//LightShooter Spaceship animations
	if (sprite_path == nullptr) {
		LOG("Error loading LightShooter's textures. SDL Error: %s", SDL_GetError());
	}

	

	up.PushBack({1,1,22,31}); //Facing down

	//Animation from facing downwards to facing right
	down_right.PushBack({ 24,1,25 ,29 });
	down_right.PushBack({ 52,1,27,25 });
	down_right.PushBack({ 80,1,30,22 });
	down_right.speed = 0.5f;

	right.PushBack({113,1,31,30}); //Facing right
	
	//Animation from right to up

	right_up.PushBack({ 146,1,30,22 });
	right_up.PushBack({ 181,1,27,25 });
	right_up.PushBack({ 211,1,25,29 });
	right_up.speed = 0.5f;

	up.PushBack({241,1,22,31 }); //Facing up

	//Animation from up to left

	up_left.PushBack({ 266,1,25,29 });
	up_left.PushBack({ 293,1,27,25 });
	up_left.PushBack({ 321,1,30,22 });
	up_left.speed = 0.5f;

	left.PushBack({356,1,31,29}); //Facing left

	//Animation from left to down

	left_down.PushBack({ 392,1,30,22 });
	left_down.PushBack({ 426,1,27,26 });
	left_down.PushBack({ 458,1,24,30 });
	left_down.speed = 0.5f;

	animation = &down;

	score_points = 130;
	hits_life = 1.0f;

	collider = App->collision->AddCollider({ 0, 0, 31, 31 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies); 
}

void LightShooter_Spaceship::Move() {


}

void LightShooter_Spaceship::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {
	
}

void LightShooter_Spaceship::OnCollision(Collider*collider, int num_enemy) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		hits_life -= App->player->hit_dmg;
	}
	else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
		hits_life -= App->player2->hit_dmg;

	}
	if (hits_life <= 0) {
		App->player->score += score_points;
		delete App->enemies->enemies[num_enemy];
		App->enemies->enemies[num_enemy] = nullptr;
		App->particles->AddParticle(explosion, position.x, position.y);
	}

}