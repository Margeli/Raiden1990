#include "Application.h"
#include "BonusSpaceship.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"
#include "math.h"


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
	explosion.anim.speed = 0.3f;

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
		Shot(color_rotatory_shot, { App->player->position.x+11 ,App->player->position.y+13 }, { position.x + 31,  position.y + 25 });//Adds a particle (color_rotatory_shot) in front of the spaceship.
		shooting = false;
	}	

	if(increment_y<80) 
	speed = 0.5f;
	

	else if ((increment_y >= 80)&&(increment_y<550)) {//enemy entrance
		animation = &idle;

		if (increment_y <= 90|| increment_y>=540) { 
			animation = &boost;		
		}		

		speed = 0.7f;
		if ((int)increment_y == 100|| (int)increment_y == 200|| (int)increment_y == 300) {
			shooting = true; //shots at 100, 200 & 300
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
}

void Bonus_Spaceship::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {
	unitary = { 0,0 };
	shot.speed ={0,0};
	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT);
	delta_x = (float)aim_position.x - shot_initial_pos.x;
	delta_y = (float)aim_position.y - shot_initial_pos.y;
	vector_lenght = sqrt(delta_x*delta_x + delta_y*delta_y); //length between Enemy pos & Player pos
	/*
	m = vector_lenght / 2.0f;
	shot.speed.y = -2.0f;
	shot.speed.y -= delta_y / m;
	shot.speed.x = delta_x / m;
	*/
	
	if (aim_position.y > shot_initial_pos.y) {
	
	}
	
	

	
	
	unitary.x = delta_x / vector_lenght;
	unitary.y = delta_y / vector_lenght;
	unitary.x *= 2.0f;
	unitary.y *= 2.0f;	
	
	shot.speed.y = unitary.y;
	shot.speed.x = unitary.x;
}


void Bonus_Spaceship::OnCollision(Collider*collider, int num_enemy) {
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
		App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);
		
	}

}