#ifndef __BONUS_SPACESHIP_H__
#define __BONUS_SPACESHIP_H__

#include "Enemy.h"

class Bonus_Spaceship : public Enemy
{
private:

	
	Animation idle;
	Animation forward;
	Animation boost;
	float speed ;
	float increment_y;
	float initial_y;
	int counter_movement;
	bool right;
	void Shot(int shooter_x, int shooter_y);
	bool shooting ;

public:

	Bonus_Spaceship(int x, int y, int count);
	void Move();
	int shoots = 3;

	

};

#endif // __STATIC_ENEMY_H__