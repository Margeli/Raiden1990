#ifndef __MINE_H__
#define __MINE_H__

#include "Enemy.h"
#include "ModuleParticles.h"
#include "Path.h"

class Mine : public Enemy
{
private:
	
	Animation idle;
	Particle explosion;
	Particle color_rotatory_shot;
	Mix_Chunk* fx_shoot = nullptr;
	fPoint original_pos;
	void OnCollision(Collider* collider, int num_enemy);


	float speed;
	bool b_right = false;
	bool b_left = false;
	bool downwards = true;
	
	float hits_life;
	int shoot_number = 0;
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	uint score_points;





public:

	Mine(int x, int y, int shoot_num);
	void Move();


	

};

#endif// __MINE_H__