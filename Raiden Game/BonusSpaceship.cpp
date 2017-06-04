#include "Application.h"
#include "BonusSpaceship.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"
#include "math.h"
#include "ModulePowerUps.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

Bonus_Spaceship::Bonus_Spaceship (int x, int y, int count) : Enemy(x, y) 
{
	sprite_path = App->textures->Load("Assets/Images/Bonus_Spaceship.png");

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
	explosion.anim.PushBack({ 154, 534, 77, 68 });
	explosion.anim.PushBack({ 231, 534, 77, 68 });
	explosion.anim.PushBack({ 308, 534, 77, 68 });
	explosion.anim.PushBack({ 385, 534, 77, 68 });
	explosion.anim.PushBack({ 0,0,0,0 });
	explosion.anim.speed = 0.2f;
	explosion.life = 1000;

	//Bonus Spaceship shot
	color_rotatory_shot.anim.PushBack({ 22, 40, 6, 7 });	
	color_rotatory_shot.anim.PushBack({ 39, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({56, 40, 6, 7 });//animation
	color_rotatory_shot.anim.speed = 0.3f;
	
	color_rotatory_shot.life = 6000;
	color_rotatory_shot.anim.loop = true;

	idle.PushBack({ 45, 29,64,65 });
	idle.PushBack({ 114,29,64,65 });
	idle.PushBack({ 183,29,64,65 });
	idle.PushBack({ 252,29,64,65 });
	idle.PushBack({ 318,29,64,65 });
	idle.PushBack({ 252,29,64,65 });
	idle.PushBack({ 183,29,64,65 });
	idle.PushBack({ 114,29,64,65 });
	idle.PushBack({ 45, 29,64,65 });

	boost.PushBack({ 45,101,64,65 });

	forward.PushBack({ 114,101,64,65 });
	forward.PushBack({ 183,101,64,65 });
	forward.speed = 0.5f;
	
	animation = &forward;
	idle.speed = 0.03f;

	shoot_number = count;

	initial_y = y;
	increment_y = 0.0f;
	counter_movement = 0;
	right = true;

	
	collider = App->collision->AddCollider({ 0, 0, 64, 65 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	score_points = 480;
	hits_life= 17.0f;
	
	
}

void Bonus_Spaceship::Move() {
	
	increment_y = -(position.y - initial_y);

	if (shooting) {
		Shot(color_rotatory_shot, { App->player->position.x + 70 ,App->player->position.y-10 }, { position.x + 31,  position.y + 25 });
		Shot(color_rotatory_shot, { App->player->position.x - 70 ,App->player->position.y-10 }, { position.x + 31,  position.y + 25 });
		Shot(color_rotatory_shot, { App->player->position.x + 11 ,App->player->position.y + 13 }, { position.x + 31,  position.y + 25 });//Adds a particle (color_rotatory_shot) in front of the spaceship.
		shooting = false;
	}	

	if(increment_y<80) 
	speed = 0.4f;
	

	else if ((increment_y >= 80)&&(increment_y<550)) {//enemy entrance
		animation = &idle;

		if (increment_y <= 90|| increment_y>=540) { 
			animation = &boost;		
		}		

		speed = 0.6f;

		if (increment_y >= 100  && shoot_number==3) {
			shooting = true; //shots at 100
			shoot_number--;
		}

		if (increment_y >= 200 && shoot_number==2) {
			shooting = true; //shots at 200
			shoot_number--;
		}
		if (increment_y >= 300 && shoot_number==1) {
			shooting = true; //shots at 300
			shoot_number--;
		}

		
		if (right) {
			position.x+=0.3f;
			counter_movement++;
			
			if (counter_movement ==50) {//every 50 loops changes direction from left to right
				right = false;			
			}
		}
		else if (!right) {
			position.x -= 0.3f;
			counter_movement--;
			if (counter_movement == -50) {//every 50 loops changes direction from right to left
				right = true;
			}		
		}
	}

	else if (increment_y >= 550){  //enemy escape
		speed = 0.5f;
		animation = &forward;
	}

	

position.y -= speed;
collider->SetPos(position.x, position.y);
}

void Bonus_Spaceship::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {
	
	shot.speed ={0,0};

	if ((int)shot_initial_pos.y <aim_position.y){//down 
		if (aim_position.y - shot_initial_pos.y < 75)
			shot.speed.y = 1.0f;
		else if ((aim_position.y - shot_initial_pos.y > 75) && (aim_position.y - shot_initial_pos.y < 150))
			shot.speed.y = 2.0f;
		else if (aim_position.y - shot_initial_pos.y > 150)
			shot.speed.y = 3.0f;
	}
	
	
	else if ((int)shot_initial_pos.y >aim_position.y) {//up
		if (aim_position.y - shot_initial_pos.y < 75)
			shot.speed.y = -3.0f;
		else if ((aim_position.y - shot_initial_pos.y > 75) && (aim_position.y - shot_initial_pos.y < 150))
			shot.speed.y = -5.0f;
		else if (aim_position.y - shot_initial_pos.y > 150)
			shot.speed.y = -7.0f;
	}

	
	if ((int)shot_initial_pos.x <aim_position.x) {//right
		if (aim_position.x - shot_initial_pos.x < 75)
			shot.speed.x = 1.0f;
		else if ((aim_position.x - shot_initial_pos.x > 75)&& (aim_position.x - shot_initial_pos.x < 150))
			shot.speed.x =3.0f;
		else if (aim_position.x - shot_initial_pos.x > 150)
			shot.speed.x = 5.0f;
	}
	if ((int)shot_initial_pos.x >aim_position.x) {//left
		if (aim_position.x - shot_initial_pos.x < 75)
			shot.speed.x = -1.0f;
		else if ((aim_position.x - shot_initial_pos.x > 75) && (aim_position.x - shot_initial_pos.x < 150))
			shot.speed.x = -3.0f;
		else if (aim_position.x - shot_initial_pos.x > 150)
			shot.speed.x = -5.0f;
	}
	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT);
	
}


void Bonus_Spaceship::OnCollision(Collider*collider, int num_enemy) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		hits_life -= App->player->hit_dmg;	
	}

	else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
		hits_life -= App->player2->hit_dmg;
	}

	else if (collider->type == COLLIDER_BOMB || collider->type == COLLIDER_BOMB2) {// FIX IF PLAYER 2 THROWS BOMB
		hits_life -= App->player->bomb_dmg;		
	}

	if (hits_life <= 0) {
			Dead(collider, num_enemy);
		}
}

void Bonus_Spaceship::Dead(Collider* shooter, int num_enemy) {
	if (shooter->type == COLLIDER_PLAYER_SHOT|| shooter->type == COLLIDER_BOMB) {
		App->player->score += score_points;	
	}
	else if (shooter->type == COLLIDER_PLAYER2_SHOT || shooter->type == COLLIDER_BOMB2) {
		App->player2->score += score_points;
	}

	App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);
	if (SDL_GetTicks() % 2 == 0) { //50% RED
		App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_RED, position.x + 32, position.y + 32);
	}
	else {//50% BLUE
		App->powerup->AddPowerUp(POWERUP_TYPES::POWERUP_BLUE, position.x + 32, position.y + 32);
	}
	fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_BigSpaceship_Explosion.wav");
	if (!fx_shoot) {
		LOG("Error loading shoot's fx: %s", Mix_GetError)
	}
	App->audio->Play_Fx(fx_shoot);
	delete App->enemies->enemies[num_enemy];
	App->enemies->enemies[num_enemy] = nullptr;

}