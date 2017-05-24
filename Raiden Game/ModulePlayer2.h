#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleParticles.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void Dead();

public:

	Particle basic_shot;
	Particle left_basic_shot;
	Particle right_basic_shot;
	Particle triple_shot;
	Particle left_triple_shot;
	Particle right_triple_shot;
	Particle ext_left_triple_shot;
	Particle ext_right_triple_shot;
	Particle bomb;

	Particle misile_left;
	Particle misile_mid;
	Particle misile_right;

	Particle laser_shot;
	Particle big_laser_shot;

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation* shadow_animation = nullptr;
	Animation idle;
	Animation right;
	Animation left;
	Animation boost;
	Animation backward;
	Animation shadow_idle;
	Animation shadow_right;
	Animation shadow_left;
	Particle dead_explosion;
	Particle bomb_explosion;
	iPoint position;
	iPoint saved_position;
	iPoint shadow_position;
	Collider* spaceship_collider;
	bool destroyed = false;
	bool player2 = false;
	float hit_dmg;
	bool godmode = false;



};

#endif