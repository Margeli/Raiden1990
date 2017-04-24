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
#include "ModuleFonts.h"
#include "ModuleStageCompleted.h"
#include "ModuleLevel1.h"

#include<stdio.h>

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	user_interface = "    1UP   HI_SCORE    2UP";
	
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

	//Raiden basic shot 
	
	basic_shot.anim.PushBack({ 22, 31, 5, 5 });	//animation
	basic_shot.anim.speed = 1.0f;
	basic_shot.speed.y = -3;
	basic_shot.speed.x = 0;
	basic_shot.life = 3000;
	basic_shot.anim.loop = true;

	hit_dmg = 1.0f;
	
}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	//if (spaceship_collider != nullptr) {
	//	spaceship_collider->to_delete = true;
	//}

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
	
	if (App->player2->player2==false) { 

		position.x = 111; //position if there's only 1 player
		position.y = 150;
	}
	else {

		position.x = 71; //position if there are 2 players
		position.y = 150;
	}
	
	red_font_score = App->fonts->Load("Assets/Images/Font.png", "> ?@ABCDEFGHIJKLMNOPQRSTUVWXYZ!¡?_*#$%&'()x+.-,;[].{.}./0123456789:", 3);
	yellow_font_score = App->fonts->Load("Assets/Images/Font.png", "> ?@ABCDEFGHIJKLMNOPQRSTUVWXYZ!¡?_*#$%&'()x+.-,;[].{.}./0123456789:", 3);
	
	
	// * -> "
	// [ -> tm
	//	]. -> Pts
	//	{. -> Cts
	//	}. -> Pcs

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
	
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)//GOD MODE
	{
		if (spaceship_collider!=nullptr){
			spaceship_collider->SetPos(-1000, -1000);
			spaceship_collider = nullptr;
			godmode = true;
		}
		else {
			spaceship_collider = App->collision->AddCollider({ 0,0, 23, 26 }, COLLIDER_PLAYER, this);

			godmode = false;
		}
		
		
		
	}


	if ((spaceship_collider == nullptr) && (godmode == false)) {

		spaceship_collider = App->collision->AddCollider({ 0,0, 23, 26 }, COLLIDER_PLAYER, this);
		spaceship_collider->SetPos(position.x, position.y);
	}




	if( (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)&&(App->fade->IsFading()==false))//DIRECT WIN/LOSE
	{
		App->fade->FadeToBlack(this, App->stageCompleted);		

	}

  	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{			
 		App->particles->AddParticle(basic_shot, position.x + 9 , position.y, COLLIDER_PLAYER_SHOT,0,"Assets/Audio/Fx_Simple_Shot.wav");//Adds a particle (basic_shot) in front of the spaceship.
	}

	if (spaceship_collider!= nullptr)
		spaceship_collider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

		// Draw UI (score) --------------------------------------

		if (score >= high_score)
			high_score = score;





		sprintf_s(score_text, 10, "%7d", score);
		sprintf_s(high_score_text, 10, "%7d", high_score);
		
		App->fonts->BlitText(0,1,red_font_score, user_interface);
		App->fonts->BlitText(0, 9, yellow_font_score, score_text);
		App->fonts->BlitText(88,9, yellow_font_score, high_score_text);
	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	switch (c2->type) {
	case COLLIDER_POWERUP_MEDAL:
		score += 500;
		break;

	case COLLIDER_ENEMY_SHOT :
		if ((c1 == spaceship_collider && destroyed == false && App->fade->IsFading() == false)) {
			App->player2->player2 = false;
			App->fade->FadeToBlack((Module*)App->level1, (Module*)App->intro);
			destroyed = true;

			score = 0;
			App->level1->first = false;

		}
	case COLLIDER_ENEMY:
		if ((c1 == spaceship_collider && destroyed == false && App->fade->IsFading() == false)) {
			App->player2->player2 = false;
			App->fade->FadeToBlack((Module*)App->level1, (Module*)App->intro);
			destroyed = true;
			score = 0;
			App->level1->first = false;

		}

	}
}