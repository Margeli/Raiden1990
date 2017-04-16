#include "Application.h"
#include "BonusSpaceship.h"
#include "ModuleCollision.h"

Bonus_Spaceship::Bonus_Spaceship (int x, int y) : Enemy(x, y) 
{
	fly.PushBack({ 45,43,59,50 });
	fly.PushBack({ 115,43,59,50 });
	fly.PushBack({ 184,43,59,50 });
	fly.PushBack({ 253,43,59,50 });
	fly.PushBack({ 319,43,59,50 });
	animation = &fly;

	initial_y = y;
	increment_y = 0.0f;
	counter_movement = 0;
	right = true;
	
	collider = App->collision->AddCollider({ 0, 0, 59, 50 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	 
	
		
}

void Bonus_Spaceship::Move() {

	increment_y = -(position.y - initial_y);
	if(increment_y<30)
	speed = 0.5f;
	

	else if ((increment_y >= 30)&&(increment_y<350)) {//enemy entrance
		speed = 0.7f;
		if (right) {
			position.x+=0.3f;
			counter_movement++;
			if (counter_movement ==50) {
				right = false;			
			}
		}
		else if (!right) {//enemy side to side
			position.x -= 0.3f;
			counter_movement--;
			if (counter_movement == -50) {
				right = true;
			}		
		}
	}

	else if (increment_y >= 350){  //enemy escape
		speed = 0.5f;
		
	}

	

position.y -= speed;
}
