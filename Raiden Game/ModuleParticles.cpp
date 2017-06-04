#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;	

}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
		graphics = App->textures->Load("Assets/Images/Particles_Spritesheet.png");

	if (graphics == nullptr) {
		LOG("Error loading particles");
	}	

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	LOG("Unloading fx");
	App->audio->Unload_Fx(fx_shoot);


	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			if (p->to_delete) {
			delete p;
			active[i] = nullptr;
			}
			
		}
		else //if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, char* FX_path)
{
	 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			if (particle.fx_played == false) //Fx sound when shooting
			{

				fx_shoot = App->audio->Load_Fx(FX_path);
				if (!fx_shoot) {
					LOG("Error loading shoot's fx: %s", Mix_GetError)
				}
				App->audio->Play_Fx(fx_shoot);
				particle.fx_played = false;
			}

			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks();			
			p->position.x = x;
			p->position.y = y;
			p->delay = delay;
			if (collider_type != COLLIDER_NONE) {
				p->collider = App->collision->AddCollider( p->anim.GetCurrentFrame() , collider_type, this);
				active[i] = p;
				break;
			}
		}
	}
} 
	

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide (except bombs )
		if (active[i] != nullptr && active[i]->collider == c1)
		{	
			if (c1->type == COLLIDER_BOMB || c1->type == COLLIDER_BOMB2) {}
			
			else
			{
				//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
				delete active[i];
				active[i] = nullptr;
				break;
			
							
			}
		}
	}
}
// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life), delay(p.delay)
{}

iPoint Particle::GetPos() const {
	return position;
}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;

}
bool Particle::Update()
{
	bool ret = true;
	uint particle_life = SDL_GetTicks() - born;
	if (life > 0)
	{
		if (particle_life < delay) {
			ret = false;
		}
		else if (particle_life > life + delay) {
			to_delete = true;
			ret = false;
		}
		else {
			position.x += speed.x;
			position.y += speed.y;
		}

	}
	else
		if (anim.Finished())
			ret = false;

	
	
	
	if (collider != nullptr) {
		collider->SetPos(position.x, position.y);
	}

	return ret;
}