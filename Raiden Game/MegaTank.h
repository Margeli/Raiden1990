#ifndef __MEGATANK_H__
#define __MEGATANK_H__

#include "Enemy.h"
#include "ModuleParticles.h"

class MegaTank : public Enemy
{
private:

	Animation idle_forward;
	Animation idle_side;
	Animation forward;
	Animation sideward;
	Particle explosion;
	Particle color_rotatory_shot;
	Mix_Chunk* fx_shoot = nullptr;
	void OnCollision(Collider* collider, int num_enemy);

	fPoint initial;
	fPoint increment;
	


	float hits_life;
	int shoot_number = 0;
	void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos);
	uint score_points;
	Uint32 shot_timer;
	Uint32 start;
	
	bool to_right;
	bool move_up = false;


public:
	void MegaTank::ShotVector(Particle& shot, iPoint velocity_vector, fPoint shot_initial_pos, uint delay=0);
	MegaTank(int x, int y, bool right);
	void Move();




};

#endif// __MEGATANK_H__