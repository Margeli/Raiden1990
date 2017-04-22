#ifndef __MODULEPOWERUPS_H__
#define __MODULEPOWERUPS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#define MAX_POWERUPS 10

struct SDL_Texture;

struct PowerUp;

enum POWERUP_TYPES {
		POWERUP_NONE = -1,
		POWERUP_BLUE,
		POWERUP_RED,
		POWERUP_H,
		POWERUP_M,
		POWERUP_P,
		POWERUP_MEDAL,
		POWERUP_DRAGON,
		POWERUP_FAIRY,	
	};

class ModulePowerUps : public Module{
	

	public:
		ModulePowerUps();
		~ModulePowerUps();

		bool Start();
		update_status Update();
		bool CleanUp();
		void OnCollision(Collider* c1, Collider* c2);
		void AddPowerUp( POWERUP_TYPES type, int x, int y);

		char* sprites_path;
		

public:
	Particle Red_Bonus;
	Particle Blue_Bonus;
	Particle M_Bonus;
	Particle H_Bonus;
	Particle P_Bonus; 
	Particle Fairy_Bonus;
	Particle Medal_Bonus;
	Particle Dragon_Bonus;
			
};

#endif //__MODULEPOWERUPS_H__

