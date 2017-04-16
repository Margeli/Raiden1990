#include "Application.h"
#include "BonusSpaceship.h"
#include "ModuleCollision.h"

Bonus_Spaceship::Bonus_Spaceship (int x, int y) : Enemy(x, y) 
{
	fly.PushBack({ 51,53,114,95 });
	fly.PushBack({ 185,53,35,28 });
	fly.PushBack({ 316,53,35,28 });
	fly.PushBack({ 445,53,35,28 });
	fly.PushBack({ 571,53,35,28 });
	animation = &fly;

	
	collider = App->collision->AddCollider({ 0, 0, 35, 28 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

