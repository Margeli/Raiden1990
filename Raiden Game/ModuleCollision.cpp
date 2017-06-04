#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_BOX][COLLIDER_BOX] = false;
	matrix[COLLIDER_BOX][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BOX][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BOX][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_BOX][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BOX][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_BOX][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_BOX][COLLIDER_PLAYER2_SHOT] = true;
	matrix[COLLIDER_BOX][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_BOX][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_BOX][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_BOX][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_BOX][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_BOX][COLLIDER_BOMB] = true;
	matrix[COLLIDER_BOX][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_BOX][COLLIDER_POWERUP_MEDAL] = false;
	matrix[COLLIDER_BOX][COLLIDER_BOMB2] = true;
	

	matrix[COLLIDER_PLAYER][COLLIDER_BOX] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_EXPLOSION] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP_B] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP_R] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP_M] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP_BLUE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP_P] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_BOMB] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP_DRAGON] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWERUP_MEDAL] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_BOX] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER2_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_BOMB] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_BOMB2] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWERUP_MEDAL] = false;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOX] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOMB] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_POWERUP_MEDAL] = false;



	matrix[COLLIDER_PLAYER2][COLLIDER_BOX] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_EXPLOSION] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_POWERUP_B] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_POWERUP_R] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_POWERUP_M] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_POWERUP_BLUE] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_POWERUP_P] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_BOMB] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_POWERUP_DRAGON] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_POWERUP_MEDAL] = true;

	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_BOX] = true;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_BOMB] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_PLAYER2_SHOT][COLLIDER_POWERUP_MEDAL] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BOX] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BOMB] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWERUP_MEDAL] = false;

	matrix[COLLIDER_EXPLOSION][COLLIDER_BOX] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_BOMB] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_EXPLOSION][COLLIDER_POWERUP_MEDAL] = false;

	

	matrix[COLLIDER_POWERUP_B][COLLIDER_BOX] = false;	 //POWER UP COLLIDERS
	matrix[COLLIDER_POWERUP_B][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP_B][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP_B][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP_B][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP_B][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_POWERUP_B][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_POWERUP_B][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_POWERUP_B][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_POWERUP_B][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_POWERUP_B][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_POWERUP_B][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_POWERUP_B][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_POWERUP_B][COLLIDER_BOMB] = false;
	matrix[COLLIDER_POWERUP_B][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_POWERUP_B][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_POWERUP_B][COLLIDER_POWERUP_MEDAL] = false;
	

	matrix[COLLIDER_POWERUP_R][COLLIDER_BOX] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP_R][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_POWERUP_R][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_BOMB] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_POWERUP_R][COLLIDER_POWERUP_MEDAL] = false;
	

	matrix[COLLIDER_POWERUP_M][COLLIDER_BOX] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP_M][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_POWERUP_M][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_BOMB] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_POWERUP_M][COLLIDER_POWERUP_MEDAL] = false;
	

	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_BOX] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_BOMB] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_POWERUP_BLUE][COLLIDER_POWERUP_MEDAL] = false;
	

	matrix[COLLIDER_POWERUP_P][COLLIDER_BOX] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP_P][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_POWERUP_P][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_BOMB] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_POWERUP_P][COLLIDER_POWERUP_MEDAL] = false;
	

	matrix[COLLIDER_BOMB][COLLIDER_BOX] = true;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_BOMB][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_BOMB][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_BOMB][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_BOMB][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_BOMB][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_BOMB][COLLIDER_BOMB] = false;
	matrix[COLLIDER_BOMB][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_BOMB][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_BOMB][COLLIDER_POWERUP_MEDAL] = false;

	matrix[COLLIDER_BOMB2][COLLIDER_BOX] = true;
	matrix[COLLIDER_BOMB2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_BOMB2][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_BOMB] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_BOMB2][COLLIDER_POWERUP_MEDAL] = false;


	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_BOX] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_BOMB] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_POWERUP_DRAGON][COLLIDER_POWERUP_MEDAL] = false;
	

	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_BOX] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_EXPLOSION] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_PLAYER2_SHOT] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_POWERUP_B] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_POWERUP_R] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_POWERUP_M] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_POWERUP_BLUE] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_POWERUP_P] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_BOMB] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_BOMB2] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_POWERUP_DRAGON] = false;
	matrix[COLLIDER_POWERUP_MEDAL][COLLIDER_POWERUP_MEDAL] = false;
	

	

}

ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN || App->input->gamepad[7] == KEY_STATE::KEY_REPEAT)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_BOX: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_PLAYER2: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_PLAYER2_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_EXPLOSION: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_POWERUP_R: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_POWERUP_B: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_POWERUP_M: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_POWERUP_BLUE: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_POWERUP_P: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_BOMB: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_BOMB2: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_POWERUP_MEDAL: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_POWERUP_DRAGON: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}