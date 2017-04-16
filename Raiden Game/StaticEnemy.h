#ifndef __STATIC_ENEMY_H__
#define __STATIC_ENEMY_H__

#include "Enemy.h"

class Static_Enemy : public Enemy
{
private:

	
	Animation fly;

public:

	Static_Enemy(int x, int y);
	//void Move();

};

#endif // __STATIC_ENEMY_H__