#include "Application.h"
#include "GreenShooterSpaceship.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"


GreenShooter_Spaceship::GreenShooter_Spaceship(int x, int y, int count) : Enemy(x, y)
{
	

	//explosion  particle animation (2nd row particle spritesheet.)
	explosion.anim.PushBack({ 2,60,34,30 });
	explosion.anim.PushBack({ 36 ,60,34,30 });
	explosion.anim.PushBack({ 70,60,34,30 });
	explosion.anim.PushBack({ 104 ,60,34,30 }); // test explosion (this explosion is LightShooter's one.)
	explosion.anim.PushBack({ 138 ,60,34,30 });
	explosion.anim.PushBack({ 172 ,60,34,30 });
	explosion.anim.PushBack({ 206 ,60,34,30 });
	explosion.anim.PushBack({ 240,60,34,30 });
	explosion.anim.PushBack({ 274,60,34,30 });
	explosion.anim.PushBack({ 308 ,60,34,30 });
	explosion.anim.PushBack({ 342,60,34,30 });
	explosion.anim.PushBack({ 376 ,60,34,30 });
	explosion.anim.PushBack({ 410,60,34,30 });
	explosion.anim.PushBack({ 446 ,60,34,30 });
	explosion.anim.PushBack({ 478 ,60,34,30 });
	explosion.anim.PushBack({ 512,60,34,30 });
	explosion.anim.PushBack({ 0,0,0,0 });
	explosion.anim.speed = 0.3f;

	explosion.life = 6000;
	explosion.anim.loop = false;

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

	score_points = 130;
	hits_life = 5.0f;// 21.0f
	down = true;
	
	collider = App->collision->AddCollider({ 0, 0, 71, 53 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void GreenShooter_Spaceship::Move() {
	increment_y = (position.y - initial_y);

	if (lineal_shoot) {	//shots 6 bullets sequentially
		
		
		
		lineal_shoot = false;
	}

	if (disperse_shoot) {//shots 8 bullets at the same time
		


		disperse_shoot = false;
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
			if ((int)increment_y == 140) {
				disperse_shoot = true;
			}
		}
		else if (increment_y < -200) {
			speed = -3.0f;
			animation = &backward_boost;
		}
	}
	position.y += speed;
	
}

void GreenShooter_Spaceship::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {	
	shot.speed = { 0,0 };
	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT);
}





void GreenShooter_Spaceship::OnCollision(Collider*collider, int num_enemy){
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		hits_life-= App->player->hit_dmg;
	}
	else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
		hits_life -= App->player2->hit_dmg;
	
	}
	if (hits_life <= 0) {
		App->player->score += score_points;
		App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION, 0, "Assets/Images/Particles_Spritesheet.png");





		delete App->enemies->enemies[num_enemy];
		App->enemies->enemies[num_enemy] = nullptr;
		
	}

}