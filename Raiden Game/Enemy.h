#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModuleParticles.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Animation* animation = nullptr;
	Collider* collider = nullptr;
	

public:
	fPoint position;
	SDL_Texture* sprite_path = nullptr;

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	float hits_life ;
	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos)=0;
	//virtual void ShotMovement()=0;
	virtual void OnCollision(Collider* collider, int num_enemy);
};

#endif  __ENEMY_H__
