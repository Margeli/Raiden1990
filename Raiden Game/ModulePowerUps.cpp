#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePowerUps.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"

ModulePowerUps::ModulePowerUps()
{

}

ModulePowerUps::~ModulePowerUps()
{

}

bool ModulePowerUps::CleanUp()
{
	LOG("Unloading power-ups");

	App->textures->Unload(powerup);

	if (pu_collider != nullptr) {
		pu_collider->to_delete = true;
	}

	return true;
}

bool ModulePowerUps::Start()
{

	return true;
}

update_status ModulePowerUps::Update()
{
	return UPDATE_CONTINUE;

}

void ModulePowerUps::OnCollision(Collider* c1, Collider* c2)
{

}

void ModulePowerUps::AddPowerUp(Particle*particle, POWERUP_TYPE type, int x, int y)
{	
	if (particle != nullptr) {


		switch (type)
		{
		case POWERUP_BLUE: 
			
			break;
		case POWERUP_RED: 

			break;
		case POWERUP_H: 

			break;
		case POWERUP_M: 

			break;
		case POWERUP_P: 

			break;
		case POWERUP_DRAGON: 

			break;
		case POWERUP_FAIRY: 

			break;
		case POWERUP_MEDAL: 

			break;

		}
	}
}