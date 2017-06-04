#ifndef __BOSSCANNON2_H__
#define __BOSSCANNON2_H__


#include "Enemy.h"
#include "ModuleParticles.h"

class BossCannon2 : public Enemy
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
	Uint32 timer_shot;






public:

	BossCannon2(int x, int y, int shoot_num);
	void Move();




};

#endif// __BOSSCANNON2_H__
