#ifndef __BOX_H__
#define __BOX_H__

#include "Enemy.h"
#include "ModuleParticles.h"

class Box : public Enemy
{
private:


	Animation idle;
	Particle explosion;	
	Mix_Chunk* fx_shoot = nullptr;
	void OnCollision(Collider* collider, int num_enemy);
	
	float hits_life;
	int shoot_number = 0;
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	
public:

	Box(int x, int y);
	void Move();




};

#endif// __BOX_H__