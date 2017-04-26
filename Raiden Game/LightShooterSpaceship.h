#ifndef __LIGHTSHOOTER_SPACESHIP_H__
#define __LIGHTSHOOTER_SPACESHIP_H__

#include "Enemy.h"
#include "ModuleParticles.h"
#include "Path.h"

class LightShooter_Spaceship : public Enemy
{
private:

	Path path;
	fPoint original_pos;
	int initial_count;
	Animation down;
	Animation right;
	Animation left;
	Animation up;
	Animation down_right;
	Animation right_up;
	Animation up_left;
	Animation left_down;
	Animation left_downwards;
	Animation downwards_right;

	Particle explosion;
	Mix_Chunk* fx_shoot = nullptr;

	bool move;
	float speed;
	float increment_y;
	int initial_y;		
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	bool shooting;
	
	bool downwards=true;
	

	void OnCollision(Collider* collider, int num_enemy);


public:

	LightShooter_Spaceship(int x, int y, int count);
	void Move();

};

#endif //__LIGHTSHOOTER_SPACESHIP__