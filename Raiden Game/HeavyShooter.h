#ifndef __HEAVYSHOOTER_H__
#define __HEAVYSHOOTER_H__

#include "Enemy.h"
#include "ModuleParticles.h"

class HeavyShooter : public Enemy
{
private:


	Animation idle;
	Animation shoot;
	Particle explosion;
	Particle color_rotatory_shot;
	Mix_Chunk* fx_shoot = nullptr;
	void OnCollision(Collider* collider, int num_enemy);

	bool first = true;
	float speed;
	float increment_y;
	float initial_y;
	Uint32 move_loop;
	Uint32 start_move_loop;
	bool right;

	float hits_life;
	int shoot_number = 0;
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	uint score_points;





public:

	HeavyShooter(int x, int y, int shoot_num);
	void Move();




};

#endif// __HEAVYSHOOTER_H__