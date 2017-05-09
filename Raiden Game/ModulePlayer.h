#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleParticles.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void Dead();

public:

	Particle basic_shot;

	Particle misile_left;
	Particle misile_right;


public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation right;
	Animation left;	
	Animation boost;
	Animation backward;	
	Animation shadow_idle;
	Animation shadow_right;
	Animation shadow_left;
	Particle explosion;
	iPoint position;
	Collider* spaceship_collider;
	bool destroyed=false;
	float hit_dmg;
	bool godmode = false;
	uint high_score = 0;
	uint score=0;

	char score_text[10];
	char high_score_text[10];
	char *user_interface;
	char *godmode_activated;

	int red_font_score = 0;
	int yellow_font_score = 0;

	
	uint red_powerup_level = 0;
	uint M_powerup_level = 0;
	
	Mix_Chunk* fx_shoot = nullptr;
	
	
};

#endif