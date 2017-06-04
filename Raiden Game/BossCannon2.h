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

	
	Mix_Chunk* fx_shoot = nullptr;
	void OnCollision(Collider* collider, int num_enemy);


	float speed;
	float increment_y;
	float initial_y;
	int player_initial_x;

	
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	




public:

	BossCannon2(int x, int y, int shoot_num);
	void Move();




};

#endif// __BOSSCANNON2_H__
