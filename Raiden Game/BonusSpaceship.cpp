#include "Application.h"
#include "BonusSpaceship.h"
#include "ModuleCollision.h"

Bonus_Spaceship::Bonus_Spaceship (int x, int y) : Enemy(x, y) 
{
	fly.PushBack({ 6,1,35,28 });
	fly.PushBack({ 6,1,35,28 });
	fly.PushBack({ 6,1,35,28 });
	fly.PushBack({ 6,1,35,28 });
	fly.PushBack({ 6,1,35,28 });
	animation = &fly;

	
	collider = App->collision->AddCollider({ 0, 0, 35, 28 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

