#ifndef __BONUS_SPACESHIP_H__
#define __BONUS_SPACESHIP_H__

#include "Enemy.h"

class Bonus_Spaceship : public Enemy
{
private:

	
	Animation fly;

public:

	Bonus_Spaceship(int x, int y);
	//void Move();

};

#endif // __STATIC_ENEMY_H__