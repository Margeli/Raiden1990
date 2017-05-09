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
	

	
	
	Red_Bonus.anim.PushBack({ 383,1,15,13 });	//Red Bonus
	Red_Bonus.anim.PushBack({ 403,1,15,13 });
	Red_Bonus.anim.PushBack({ 422,1,15,13 });	
	Red_Bonus.anim.speed = 1.5f;
	Red_Bonus.speed.y = 0;
	Red_Bonus.speed.x = 0;

	Red_Bonus.life = 60000;

	Red_Bonus.anim.loop = true;

	M_Bonus.anim.PushBack({ 440,17,15,13 });	//M_Bonus
	M_Bonus.anim.speed = 1.0f;
	M_Bonus.speed.y = 0;
	M_Bonus.speed.x = 0;
	M_Bonus.life = 60000;
	M_Bonus.anim.loop = true;
/*
	Blue_Bonus.anim.PushBack({ , , , });	//Blue_Bonus
	Blue_Bonus.anim.speed = 1.0f;
	Blue_Bonus.speed.y = 0;
	Blue_Bonus.speed.x = 0;
	Blue_Bonus.life = 60000;
	Blue_Bonus.anim.loop = true;

	H_Bonus.anim.PushBack({ , , , });	//H_Bonus
	H_Bonus.anim.speed = 1.0f;
	H_Bonus.speed.y = 0;
	H_Bonus.speed.x = 0;
	H_Bonus.life = 60000;
	H_Bonus.anim.loop = true;

	P_Bonus.anim.PushBack({ , , , });	//P_Bonus
	P_Bonus.anim.speed = 1.0f;
	P_Bonus.speed.y = 0;
	P_Bonus.speed.x = 0;
	P_Bonus.life = 60000;
	P_Bonus.anim.loop = true;

	

	Dragon_Bonus.anim.PushBack({ , , , });	//Dragon_Bonus
	Dragon_Bonus.anim.speed = 1.0f;
	Dragon_Bonus.speed.y = 0;
	Dragon_Bonus.speed.x = 0;
	Dragon_Bonus.life = 60000;
	Dragon_Bonus.anim.loop = true;

	Fairy_Bonus.anim.PushBack({ , , , });	//Fairy_Bonus
	Fairy_Bonus.anim.speed = 1.0f;
	Fairy_Bonus.speed.y = 0;
	Fairy_Bonus.speed.x = 0;
	Fairy_Bonus.life = 60000;
	Fairy_Bonus.anim.loop = true;
*/

	Medal_Bonus.anim.PushBack({ 499, 0,9,16 });	//Medal_Bonus
	Medal_Bonus.anim.speed = 1.0f;
	Medal_Bonus.speed.y = 0;
	Medal_Bonus.speed.x = 0;
	Medal_Bonus.life = 60000;
	Medal_Bonus.anim.loop = true;

	
}

ModulePowerUps::~ModulePowerUps()
{

}

bool ModulePowerUps::CleanUp()
{
	
	
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

void ModulePowerUps::AddPowerUp(POWERUP_TYPES type, int x, int y, char* FX_path)
{	

	switch (type)
		{
		case POWERUP_BLUE: 
			App->particles->AddParticle(Blue_Bonus, x, y, COLLIDER_TYPE::COLLIDER_POWERUP_BLUE);
			break;
		case POWERUP_RED: 
			App->particles->AddParticle(Red_Bonus, x, y, COLLIDER_TYPE::COLLIDER_POWERUP_R);
			break;
		case POWERUP_B: 
			App->particles->AddParticle(H_Bonus, x, y, COLLIDER_TYPE::COLLIDER_POWERUP_B);
			break;
		case POWERUP_M: 
			App->particles->AddParticle(M_Bonus, x, y, COLLIDER_TYPE::COLLIDER_POWERUP_M);
		/*	if (powerup.fx_played == false) //Fx sound when shooting
			{

				fx_shoot = App->audio->Load_Fx(FX_path);
				if (!fx_shoot) {
					LOG("Error loading shoot's fx: %s", Mix_GetError)
				}
				App->audio->Play_Fx(fx_shoot);
				particle.fx_played = false;
			}

			PowerUp* p = new PowerUp(powerup);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE) {
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
				active[i] = p;
			}*/
			break;
		case POWERUP_P: 
			App->particles->AddParticle(P_Bonus, x, y, COLLIDER_TYPE::COLLIDER_POWERUP_P);
			break;
		case POWERUP_DRAGON: 
			App->particles->AddParticle(Dragon_Bonus, x, y, COLLIDER_TYPE::COLLIDER_POWERUP_DRAGON);
			break;
		case POWERUP_FAIRY: 
			App->particles->AddParticle(Fairy_Bonus, x, y, COLLIDER_TYPE::COLLIDER_POWERUP_FAIRY);
			break;
		case POWERUP_MEDAL: 
			App->particles->AddParticle(Medal_Bonus, x, y, COLLIDER_TYPE::COLLIDER_POWERUP_MEDAL);
			break;

		}
	}
