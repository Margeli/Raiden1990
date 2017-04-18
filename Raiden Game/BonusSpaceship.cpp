#include "Application.h"
#include "BonusSpaceship.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"


Bonus_Spaceship::Bonus_Spaceship (int x, int y, int count) : Enemy(x, y) 
{
	//Bonus Spaceship shot
	color_rotatory_shot.anim.PushBack({ 22, 40, 6, 5 });	
	color_rotatory_shot.anim.PushBack({ 39, 40, 6, 5 });
	color_rotatory_shot.anim.PushBack({56, 40, 6, 5 });//animation
	color_rotatory_shot.anim.speed = 0.3f;
	
	color_rotatory_shot.life = 3000;
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

	 
	
		
}

void Bonus_Spaceship::Move() {
	
	increment_y = -(position.y - initial_y);

	if (shooting) {
		Shot(color_rotatory_shot, App->player->position);
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

void Bonus_Spaceship::ShotMovement() {
	color_rotatory_shot.speed.y = unitary.y;
	color_rotatory_shot.speed.x = unitary.x;
	
}
void Bonus_Spaceship::Shot(Particle& shot, iPoint aim_position) {
	
	App->particles->AddParticle(color_rotatory_shot, position.x + 31, position.y + 25, COLLIDER_ENEMY_SHOT);//Adds a particle (color_rotatory_shot) in front of the spaceship.
	delta_x = (float)aim_position.x - position.x;
	delta_y = (float)aim_position.y - position.y;
	vector_lenght = sqrt(delta_x*delta_x + delta_y*delta_y);
	unitary.x = delta_x / vector_lenght;
	unitary.y = delta_x / vector_lenght;
	unitary.x *= 2.0f;
	unitary.y *= 2.0f;	
}