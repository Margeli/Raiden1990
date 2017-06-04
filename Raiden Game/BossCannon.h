#ifndef __BOSSCANNON_H__
#define __BOSSCANNON_H__


#include "Enemy.h"
#include "ModuleParticles.h"

class BossCannon : public Enemy
{
private:

	Animation down;
	Animation up;
	Animation left;
	Animation right;
	Animation down_left;
	Animation down_right;
	Animation up_left;
	Animation up_right;

	
	Mix_Chunk* fx_shoot = nullptr;
	void OnCollision(Collider* collider, int num_enemy);


	float speed;
	

	
	
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	






public:

	BossCannon(int x, int y, int shoot_num);
	void Move();




};

#endif// __BOSSCANNON_H__
