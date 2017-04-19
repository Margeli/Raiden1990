#ifndef __GREENSHOOTER_SPACESHIP_H__
#define __GREENSHOOTER_SPACESHIP_H__

#include "Enemy.h"
#include "ModuleParticles.h"

class GreenShooter_Spaceship : public Enemy
{
private:


	Animation idle;	
	Animation boost;

	Animation backward_idle;
	Animation backward_boost;
	

	float speed;
	float increment_y;
	float initial_y;
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	//void ShotMovement();
	bool shooting;







public:

	GreenShooter_Spaceship(int x, int y, int count);
	void Move();




};

#endif// __GREENSHOOTER_SPACESHIP__