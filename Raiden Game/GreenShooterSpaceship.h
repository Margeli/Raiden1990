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
	Particle color_rotatory_shot;

	Mix_Chunk* fx_shoot = nullptr;
	
	
	float speed;
	float increment_y;
	float initial_y;
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	void ShotVector(Particle& shot, iPoint velocity_vector, fPoint shot_initial_pos);
	bool lineal_shoot=false;
	bool disperse_shoot = false;
	bool down;
	void OnCollision(Collider* collider, int num_enemy);
	float hits_life;
	int shoot_number = 0;
	uint score_points;





public:

	GreenShooter_Spaceship(int x, int y, int shoot_num);
	void Move();
	



};

#endif// __GREENSHOOTER_SPACESHIP__