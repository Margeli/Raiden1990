#include "Application.h"
#include "BonusSpaceship.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

Bonus_Spaceship::Bonus_Spaceship (int x, int y, int count) : Enemy(x, y) 
{

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

	if (shooting) {
		Shot(position.x+31, position.y+25);//fitted to shoot from the middle of the ship
		shooting = false;
	}

	increment_y = -(position.y - initial_y);

	if(increment_y<80)
	speed = 0.5f;
	

	else if ((increment_y >= 80)&&(increment_y<550)) {//enemy entrance
		animation = &idle;
		if (increment_y <= 90|| increment_y>=540) { 
			animation = &boost;		
		}
		

		speed = 0.7f;
		if (increment_y == 100) { shooting = true; }//shots at 100
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

void Bonus_Spaceship::Shot(int shooter_x, int shooter_y) {

	//App->particles->AddParticle(App->particles->basic_shot, position.x + 9, position.y, COLLIDER_PLAYER_SHOT);//Adds a particle (basic_shot) in front of the spaceship.
}