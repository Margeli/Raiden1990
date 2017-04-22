#ifndef __MODULEPOWERUPS_H__
#define __MODULEPOWERUPS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

struct SDL_Texture;

struct PowerUp;

class ModulePowerUps : public Module{
	public:
		ModulePowerUps();
		~ModulePowerUps();

		bool Start();
		update_status Update();
		bool CleanUp();
		void OnCollision(Collider* c1, Collider* c2);

	public:

		SDL_Texture* powerup = nullptr;
		SDL_Rect PowerUp;
		Collider* pu_collider;

};

#endif //__MODULEPOWERUPS_H__

