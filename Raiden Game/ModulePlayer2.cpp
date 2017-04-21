#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;



	idle.PushBack({ 305, 13, 24,27 });

	//move animation right

	right.PushBack({ 338, 14, 20, 27 });
	right.PushBack({ 372, 14, 15, 27 });
	right.loop = false;
	right.speed = 0.1f;

	//move animation left

	left.PushBack({ 246, 14, 20, 27 });
	left.PushBack({ 275, 14, 15, 27 });
	left.loop = false;
	left.speed = 0.1f;

	//Raiden basic shot 

	basic_shot.anim.PushBack({ 22, 31, 5, 5 });	//animation
	basic_shot.anim.speed = 1.0f;
	basic_shot.speed.y = -3;
	basic_shot.speed.x = 0;
	basic_shot.life = 3000;
	basic_shot.anim.loop = true;

	hit_dmg = 1.0f;

}

ModulePlayer2::~ModulePlayer2()
{}

bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player2");

	App->textures->Unload(graphics);

	if (spaceship_collider != nullptr) {
		spaceship_collider->to_delete = true;
	}

	return true;
}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player 2 textures");
	bool ret = true;

	graphics = App->textures->Load("Assets/Images/Raiden_Spaceship.png");
	if (graphics == nullptr) {
		LOG("Error loading player 2 textures %s", SDL_GetError);
		ret = false;
	}

	position.x = 151;
	position.y = 150;

	spaceship_collider = App->collision->AddCollider({ 0,0, 23, 26 }, COLLIDER_PLAYER2, this);

	return ret;
}

// Update: draw background
update_status ModulePlayer2::Update()
{

	float speed = 2;
	float  spaceship_speed = 1;
	position.y -= spaceship_speed;

	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT) //---UP
	{
		position.y -= speed;
		if (-position.y*SCREEN_SIZE > App->render->camera.y) {
			position.y = -App->render->camera.y / SCREEN_SIZE; //upper player limit. ------->The relation between camera.y and position.y is camera.y=-position.y*SCREEN_SIZE
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)//---DOWN
	{
		position.y += speed;
		if ((-(position.y - SCREEN_HEIGHT + 27)*SCREEN_SIZE)<App->render->camera.y) { //lower player limit (27 is height of spaceship)
			position.y = ((-App->render->camera.y / SCREEN_SIZE) - 27 + SCREEN_HEIGHT);
		}

	}


	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)//---LEFT
	{
		position.x -= speed;
		App->render->camera.x += 4;
		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
		if (App->render->camera.x >= 100) {//left camera limit
			App->render->camera.x = 100;
			if (position.x <= -48) { //left player limit
				position.x = -48;
			}
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)//---RIGHT
	{
		position.x += speed;
		App->render->camera.x -= 4;
		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
		if (App->render->camera.x <= -154) {//right camera limit
			App->render->camera.x = -154;
			if (position.x >= 275) { //right player limit
				position.x = 275;
			}
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE //check error
		&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE) {
		current_animation = &idle;
	}


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(basic_shot, position.x + 9, position.y, COLLIDER_PLAYER2_SHOT, 0, "Assets/Audio/Fx_Simple_Shot.wav");//Adds a particle (basic_shot) in front of the spaceship.
	}

	spaceship_collider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}
void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == spaceship_collider && destroyed == false && App->fade->IsFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->level1, (Module*)App->intro);



		destroyed = true;
	}
}