#ifndef __STATICCANNON_H__
#define __STATICCANNON_H__

#include "Enemy.h"
#include "ModuleParticles.h"

class StaticCannon : public Enemy
{
private:


	Animation idle;
	Particle explosion;
	Particle color_rotatory_shot;
	Mix_Chunk* fx_shoot = nullptr;
	void OnCollision(Collider* collider, int num_enemy);


	float speed;
	float increment_y;
	float initial_y;


	float hits_life;
	int shoot_number = 0;
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	uint score_points;





public:

	StaticCannon(int x, int y, int shoot_num);
	void Move();




};

#endif// __STATICCANNON_H__