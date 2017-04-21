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

	Particle explosion;
	
	
	float speed;
	float increment_y;
	float initial_y;
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	//void ShotMovement();
	bool lineal_shoot=false;
	bool disperse_shoot = false;
	bool down;
	void OnCollision(Collider* collider, int num_enemy);
	float hits_life;




public:

	GreenShooter_Spaceship(int x, int y, int count);
	void Move();
	



};

#endif// __GREENSHOOTER_SPACESHIP__