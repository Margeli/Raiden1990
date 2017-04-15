#include "Application.h"
#include "StaticEnemy.h"
#include "ModuleCollision.h"

Static_Enemy::Static_Enemy(int x, int y) : Enemy(x, y)
{

	nave.x = 415;
	nave.y = 1;
	nave.w = 323;
	nave.h = 265;

	
	collider = App->collision->AddCollider({ 0, 0, 323, 265 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

