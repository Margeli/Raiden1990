#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollision.h"


ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	
	
	idle.PushBack({ 80, 13, 24,27 });
	
	//move animation right
	
	right.PushBack({ 114, 14, 20, 27 });
	right.PushBack({ 149, 14, 15, 27 });
	right.loop = false;
	right.speed = 0.1f;

	//move animation left
	
	left.PushBack({ 51, 14, 20, 27 });
	left.PushBack({ 22, 14, 15, 27 });
	left.loop = false;
	left.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	if (spaceship_collider != nullptr) {
		spaceship_collider->to_delete = true;
	}

	return true;
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Images/Raiden_Spaceship.png"); 
	if (graphics == nullptr) {
		LOG("Error loading player textures %s", SDL_GetError);
		ret = false;
	}

	position.x = 111;
	position.y = 150;

	spaceship_collider = App->collision->AddCollider({ 0,0, 23, 26 }, COLLIDER_PLAYER, this);

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	
	float speed = 2;
	float  spaceship_speed = 2;
	position.y -= spaceship_speed;

	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) //---UP
	{
		position.y -= speed;
		if (-position.y*SCREEN_SIZE > App->render->camera.y) {
			position.y = -App->render->camera.y / SCREEN_SIZE; //upper player limit. ------->The relation between camera.y and position.y is camera.y=-position.y*SCREEN_SIZE
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)//---DOWN
	{
		position.y += speed;
		if ((-(position.y-SCREEN_HEIGHT+27)*SCREEN_SIZE)<App->render->camera.y) { //lower player limit (27 is height of spaceship)
			position.y = ((-App->render->camera.y / SCREEN_SIZE) -27+ SCREEN_HEIGHT) ;
		}
		
		}
		
	
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)//---LEFT
	{
		position.x -= speed;
		App->render->camera.x +=4;
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
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)//---RIGHT
	{
		position.x += speed;
		App->render->camera.x -= 4;
		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
		if (App->render->camera.x <= -154) {//right camera limit
			App->render->camera.x =-154;
			if (position.x >= 275) { //right player limit
				position.x = 275;
			}
		}
	}
	 
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE //check error
		&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) {
		current_animation = &idle;
	}
		

  	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
 		App->particles->AddParticle(App->particles->basic_shot, position.x + 9 , position.y, COLLIDER_PLAYER_SHOT);//Adds a particle (basic_shot) in front of the spaceship.
	}

	spaceship_collider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	
	return UPDATE_CONTINUE;
}
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == spaceship_collider && destroyed == false && App->fade->IsFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->level1, (Module*)App->intro);
		


		destroyed = true;
	}
}