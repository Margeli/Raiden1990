#include "Application.h"
#include "StaticEnemy.h"
#include "ModuleCollision.h"

Static_Enemy::Static_Enemy(int x, int y) : Enemy(x, y)
{

	nave.x = 415;
	nave.y = 6;
	nave.w = 317;
	nave.h = 265;

	
	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

