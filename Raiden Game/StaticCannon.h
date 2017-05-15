#ifndef __STATICCANNON_H__
#define __STATICCANNON_H__

#include "Enemy.h"
#include "ModuleParticles.h"

class StaticCannon : public Enemy
{
private:

	SDL_Texture* graphics = nullptr;
	SDL_Rect base;
	Animation up;
	Animation down;
	Animation right;
	Animation left;
	Animation up_left;
	Animation up_right;
	Animation down_left;
	Animation down_right;


	Particle explosion;
	Particle destroyed_base;
	Particle color_rotatory_shot;
	Mix_Chunk* fx_shoot = nullptr;
	void OnCollision(Collider* collider, int num_enemy);	

	float hits_life;	
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	uint score_points;
	Uint32 timer_shot;





public:

	StaticCannon(int x, int y, int shoot_num);
	void Move();




};

#endif// __STATICCANNON_H__