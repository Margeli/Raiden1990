#include "Application.h"
#include "LightShooterSpaceship.h"
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

	explosion.life = 6000;
	explosion.anim.loop = false;
	
	sprite_path = App->textures->Load("Assets/Images/Light_Shooter.png");

	//LightShooter Spaceship animations
	if (sprite_path == nullptr) {
		LOG("Error loading LightShooter's textures. SDL Error: %s", SDL_GetError());
	}

	up.PushBack({1,1,30,30}); //Facing down

	//Animation from facing downwards to facing right
	down_right.PushBack({ 25,1,30,30 });
	down_right.PushBack({ 53,1,30,30 });
	down_right.PushBack({ 81,1,30,30 });
	down_right.speed = 0.5f;

	right.PushBack({114,1,30,30}); //Facing right
	
	//Animation from right to up

	right_up.PushBack({ 147,1,30,30 });
	right_up.PushBack({ 182,1,30,30});
	right_up.PushBack({ 212,1,30,30 });
	right_up.speed = 0.5f;

	up.PushBack({241,1,30,30 }); //Facing up

	//Animation from up to left

	up_left.PushBack({ 266,1,30,30 });
	up_left.PushBack({ 294,1,30,30 });
	up_left.PushBack({ 322,1,30,30 });
	up_left.speed = 0.5f;

	left.PushBack({356,1,31,29}); //Facing left

	//Animation from left to down

	left_down.PushBack({ 392,1,30,30 });
	left_down.PushBack({ 426,1,30,30 });
	left_down.PushBack({ 458,1,30,30 });
	left_down.speed = 0.5f;

	animation = &down;

	initial_y = y;
	increment_y = 0.0f;

	score_points = 130;
	hits_life = 1.0f;
	downwards = true;

	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies); 
}

void LightShooter_Spaceship::Move()
{
	/*position.y = (position.y - initial_y);

	if (downwards) {
		if (increment_y < 55)
			speed = 0.3f;

		else if (increment_y > 55 && increment_y < 120) {
			speed = 1.0f;
			animation = &down;
			if (position.x < App->player->position.x) {
				&down_right;
				position.x++;
			}
			else if (position.x > App->player->position.x) {
				&left_down;
				position.x--;
			}

			else if (increment_y >= 120) {
				downwards = false;
				speed = -2.0f;
				animation = &up;
			}
		}
		else
		{
			if (increment_y < 120 && increment_y>-200) {
				speed = -2.3f;
			}
			else if (increment_y < -200) {
				speed = -3.0f;
				animation = &up;
			}
		}
		position.y += speed;

	}*/
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