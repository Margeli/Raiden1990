#ifndef __TANK_H__
#define __TANK_H__

#include "Enemy.h"
#include "ModuleParticles.h"

class Tank : public Enemy
{
private:

	Animation aim_down;
	Animation aim_up;
	Animation aim_left;
	Animation aim_right;
	Animation aim_down_left;
	Animation aim_down_right;
	Animation aim_up_left;
	Animation aim_up_right;
	Animation forward;
	Animation side;
	Animation forward_right;
	Animation forward_left;


	Particle explosion;
	Particle color_rotatory_shot;
	Mix_Chunk* fx_shoot = nullptr;
	void OnCollision(Collider* collider, int num_enemy);


	float speed;
	float increment_y;
	float initial_y;


	float hits_life;
	float hits_aim;
	int shoot_number = 0;
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	uint score_points;





public:

	Tank(int x, int y, int shoot_num);
	void Move();




};

#endif// __TANK_H__