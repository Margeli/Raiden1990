#include "Application.h"
#include "BonusSpaceship.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

Bonus_Spaceship::Bonus_Spaceship (int x, int y) : Enemy(x, y) 
{
	fly.PushBack({ 45,43,63,50 });
	fly.PushBack({ 115,43,63,50 });
	fly.PushBack({ 184,43,63,50 });
	fly.PushBack({ 253,43,63,50 });
	fly.PushBack({ 319,43,63,50 });
	animation = &fly;
	fly.speed = 0.05f;
	initial_y = y;
	increment_y = 0.0f;
	counter_movement = 0;
	right = true;
	shooting = false; 

	collider = App->collision->AddCollider({ 0, 0, 63, 50 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	 
	
		
}

void Bonus_Spaceship::Move() {

	if (shooting) {
		Shot(position.x+31, position.y+25);//fitted to shoot from the middle of the ship
		shooting = false;
	}

	increment_y = -(position.y - initial_y);
	if(increment_y<30)//enemy entrance
	speed = 0.5f;
	

	else if ((increment_y >= 30)&&(increment_y<350)) {//enemy middle movement
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

	else if (increment_y >= 350){  //enemy escape
		speed = 0.5f;
		
	}

	

position.y -= speed;
}

void Bonus_Spaceship::Shot(int shooter_x, int shooter_y) {

	//App->particles->AddParticle(App->particles->basic_shot, position.x + 9, position.y, COLLIDER_PLAYER_SHOT);//Adds a particle (basic_shot) in front of the spaceship.
}