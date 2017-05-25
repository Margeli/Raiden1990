#ifndef __TANK_H__
#define __TANK_H__

#include "Enemy.h"
#include "ModuleParticles.h"

class Tank : public Enemy
{
private:

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
	int player_initial_x;

	float hits_life;
	float hits_aim;
	int shoot_number = 0;
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	uint score_points;
	void Dead(Collider* shooter, int num_enemy);




public:

	Tank(int x, int y, int shoot_num);
	void Move();




};

#endif// __TANK_H__