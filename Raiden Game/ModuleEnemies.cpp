#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "BonusSpaceship.h"
#include "LightShooterSpaceship.h"
#include "GreenShooterSpaceship.h"
#include "Mine.h"
#include "HeavyShooter.h"
#include "MegaTank.h"
#include "Tank.h"
#include "StaticCannon.h"
#include "Boss.h"
#include "Box.h"




#define SPAWN_MARGIN 200


ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	//sprites = App->textures->Load("Assets/Images/Bonus_Spaceship.png");
	//sprites = App->textures->Load("Assets/Images/Green_Shooter.png");
	//sprites = App->textures->Load("Assets/Images/Light_Shooter.png");
/*
	if (sprites == nullptr) {
		LOG("Error loading enemy's sprites.");
	}*/
	
	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (SPAWN_MARGIN+ App->render->camera.y>-queue[i].y*SCREEN_SIZE)//lower spawn limit				
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].y );
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
 		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) {
			enemies[i]->Draw(enemies[i]->sprite_path); }
			

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (App->render->camera.y+(-SCREEN_HEIGHT-SPAWN_MARGIN)*SCREEN_SIZE>-enemies[i]->position.y*SCREEN_SIZE)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.y );
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, int shots, bool right)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].shots = shots;
			queue[i].right = right;

			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::BONUS_SPACESHIP:
			enemies[i] = new Bonus_Spaceship(info.x, info.y, info.shots);
			break;

		case ENEMY_TYPES::GREENSHOOTER_SPACESHIP:
			enemies[i] = new GreenShooter_Spaceship(info.x, info.y, info.shots);
			break;

		case ENEMY_TYPES::LIGHTSHOOTER_SPACESHIP:
   			enemies[i] = new LightShooter_Spaceship(info.x, info.y, info.shots);
			break;

		case ENEMY_TYPES::MINE:
			enemies[i] = new Mine(info.x, info.y, info.shots);
			break;

		case ENEMY_TYPES::HEAVY_SHOOTER:
			enemies[i] = new HeavyShooter(info.x, info.y, info.shots);
			break;

		case ENEMY_TYPES::TANK:
			enemies[i] = new Tank(info.x, info.y, info.shots);
			break;

		case ENEMY_TYPES::MEGA_TANK:
			enemies[i] = new MegaTank(info.x, info.y, info.right);
			break;

		case ENEMY_TYPES::STATIC_CANNON:
			enemies[i] = new StaticCannon(info.x, info.y, info.shots);
			break;

		case ENEMY_TYPES::BOSS:
			enemies[i] = new Boss(info.x, info.y, info.shots);
			break;

		case ENEMY_TYPES::BOX:
			enemies[i] = new Box(info.x, info.y);
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
 			enemies[i]->OnCollision(c2, i);
			
			
			break;
		}
	}
}