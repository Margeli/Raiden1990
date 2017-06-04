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
	idle.speed = 0.5f;

	shoot.PushBack({96,0,48,44 });
	shoot.PushBack({ 144,0,48,44 });
	shoot.PushBack({ 192,0,48,44 });
	shoot.PushBack({ 240,0,48,44 });
	shoot.PushBack({ 288,0,48,44 });
	shoot.PushBack({ 336,0,48,44 });
	shoot.speed = 0.5f;
	
	
	animation = &idle;

	//Heavy Shooter shot
	rotatory_shot.anim.PushBack({ 96, 37, 12, 11 });
	rotatory_shot.anim.PushBack({ 108, 37, 12, 11 });
	rotatory_shot.anim.PushBack({ 120, 37, 12, 11 });
	rotatory_shot.anim.PushBack({ 132, 37, 12, 11 });
	rotatory_shot.anim.speed = 0.3f;

	rotatory_shot.life = 3000;
	rotatory_shot.anim.loop = true;

	
	shot_explosion.anim.PushBack({ 84, 37, 12, 11 });
	shot_explosion.anim.PushBack({ 72, 37, 12, 11 });
	shot_explosion.anim.PushBack({ 0,0, 0,0 });
	shot_explosion.life = 500;
	shot_explosion.anim.loop = false;
	shot_explosion.anim.speed = 0.3f;

	explosion.anim.PushBack({ 0, 466, 77, 68 });
	explosion.anim.PushBack({ 77, 466, 77, 68 });
	explosion.anim.PushBack({ 154, 466, 77, 68 });
	explosion.anim.PushBack({ 231, 466, 77, 68 });
	explosion.anim.PushBack({ 308, 466, 77, 68 });
	explosion.anim.PushBack({ 385, 466, 77, 68 });
	explosion.anim.PushBack({ 462, 466, 77, 68 });
	explosion.anim.PushBack({ 539, 466, 77, 68 });
	explosion.anim.PushBack({ 616, 466, 77, 68 });
	explosion.anim.PushBack({ 0, 534, 77, 68 });
	explosion.anim.PushBack({ 77, 534, 77, 68 });
	explosion.anim.PushBack({ 0,0,0,0 });
	explosion.anim.speed = 0.2f;
	explosion.life = 1000;
	explosion.anim.loop = false;

	shoot_number = 5;
	initial_y = y;
	increment_y = 0.0f;


	score_points = 480;//480
	hits_life = 30.0f;// 30.0f
	move_loop = 0;
	start_move_loop = 0;

	collider = App->collision->AddCollider({ 0, 0,48, 44 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	
}

void HeavyShooter::Move() {
	if (shot) {
		animation = &shoot;
		App->particles->AddParticle(shot_explosion, position.x + 16, position.y + 37, COLLIDER_EXPLOSION);
		App->particles->AddParticle(shot_explosion, position.x + 28, position.y + 37, COLLIDER_EXPLOSION);
		Basic_shot(rotatory_shot, 0);
		
	
		shot = false;
	}
	increment_y = (position.y - initial_y); // idle movement position
	
	if (increment_y < 25&&first) { // going to initial position
		speed = 0.3f;
		
	}
	
	else if (move_loop == 0) { //starting loop
		start_move_loop = SDL_GetTicks();
		speed = -1.0f;
		first = false;
		shoot_number = 5;
		
		if (position.x+24 > App->player->position.x) //right
			right = true;		
		else  // left
			right = false;		
		move_loop = 1;//starts movement loop
	}
	else 
		move_loop = SDL_GetTicks() - start_move_loop;

	if (move_loop > 1500&&move_loop<3000) {//going diagonal
		
		if (shoot_number==5&&move_loop>1550) {
			shot = true;
			shoot_number--;
		}
		else if (shoot_number == 4 && move_loop>1850) {
			shot = true;
			shoot_number--;
		}
		else if (shoot_number == 3 && move_loop>2150) {
			shot = true;
			shoot_number--;
		}
		else if (shoot_number == 2 && move_loop>2450) {
			shot = true;
			shoot_number--;
		}
		else if (shoot_number == 1 && move_loop>2750) {
			shot = true;
			shoot_number--;
		}
		speed = 0.3f;
		if (right&&position.x > 0) 
			position.x--;
		else if (!right&&position.x < SCREEN_WIDTH) 
			position.x++;
	}
	else if (move_loop > 3000&&move_loop<3500) { //stay 
		speed = -1.0f;
		animation = &idle;
	}
	else if (move_loop > 3500&& move_loop < 5450) { //going back
		speed = -2.0f;
		if (right)
			position.x++;
		else
			position.x--;	
	}
	else if (move_loop > 5450) { //stay
		speed = -1.0f;
		move_loop = 0;//starts the loop again
		start_move_loop = 0;
	}
	position.y += speed;
	collider->SetPos(position.x, position.y);
}




void HeavyShooter::OnCollision(Collider*collider, int num_enemy) {

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


void HeavyShooter::Basic_shot(Particle& shot, Uint32 delay) {
	shot.speed = { 0,2 };
	
	App->particles->AddParticle(shot, position.x + 16, position.y+37, COLLIDER_ENEMY_SHOT, delay);

	App->particles->AddParticle(shot, position.x + 28, position.y+37, COLLIDER_ENEMY_SHOT, delay);

}
void HeavyShooter::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {}

void HeavyShooter::Dead(Collider* shooter, int num_enemy) {

	if (shooter->type == COLLIDER_PLAYER_SHOT || shooter->type == COLLIDER_BOMB) {
		App->player->score += score_points;
	}
	else if (shooter->type == COLLIDER_PLAYER2_SHOT || shooter->type == COLLIDER_BOMB2) {
		App->player2->score += score_points;
	}

	App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);
	fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_BigSpaceship_Explosion.wav");
	if (!fx_shoot) {
		LOG("Error loading shoot's fx: %s", Mix_GetError)
	}
	App->audio->Play_Fx(fx_shoot);
	delete App->enemies->enemies[num_enemy];
	App->enemies->enemies[num_enemy] = nullptr;

}