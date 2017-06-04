#include "Application.h"
#include "LightShooterSpaceship.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"


GreenShooter_Spaceship::GreenShooter_Spaceship(int x, int y, int shoot_num) : Enemy(x, y)
{
	//GreenShooter Spaceship shot
	color_rotatory_shot.anim.PushBack({ 22, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 39, 40, 6, 7 });
	color_rotatory_shot.anim.PushBack({ 56, 40, 6, 7 });//animation
	color_rotatory_shot.anim.speed = 0.3f;

	color_rotatory_shot.life = 3000;
	color_rotatory_shot.anim.loop = true;

	//explosion  particle animation
	explosion.anim.PushBack({ 0, 466, 77, 68 });
	explosion.anim.PushBack({ 77, 466, 77, 68 });
	explosion.anim.PushBack({ 154, 466, 77, 68 });
	explosion.anim.PushBack({ 231, 466, 77, 68 }); 
	explosion.anim.PushBack({ 308, 466, 77, 68 });
	explosion.anim.PushBack({ 385, 466, 77, 68 });
	explosion.anim.PushBack({ 462, 466, 77, 68 });
	explosion.anim.PushBack({ 539, 466, 77, 68 });
	explosion.anim.PushBack({ 616, 466, 77, 68 });
	explosion.anim.PushBack({ 0, 534, 77, 68 });
	explosion.anim.PushBack({ 77, 534, 77, 68 });
	explosion.anim.PushBack({ 154, 534, 77, 68 });
	explosion.anim.PushBack({ 231, 534, 77, 68 });
	explosion.anim.PushBack({ 308, 534, 77, 68 });
	explosion.anim.PushBack({ 385, 534, 77, 68 });	
	explosion.anim.PushBack({ 0,0,0,0 });
	explosion.anim.speed = 0.2f;
	explosion.life = 1000;
	explosion.anim.loop = false;

	sprite_path = App->textures->Load("Assets/Images/Green_Shooter.png");

	//GreenShooter Spaceship animations
	if (sprite_path == nullptr) {
		LOG("Error loading GreenShooter's textures. SDL Error: %s", SDL_GetError());
	}

	idle.PushBack({ 243, 48,71,53 });//no-turbo 

	boost.PushBack({165,48,71,53 });
	boost.PushBack({ 87,48,71,53 });
	boost.PushBack({ 9,48,71,53 });
	boost.speed = 0.5f;

	backward_idle.PushBack({ 243,114,71,53 });//no-turbo backwards

	backward_boost.PushBack({ 165,114,71,53 });
	backward_boost.PushBack({ 87,114,71,53 });
	backward_boost.PushBack({ 9,114,71,53 });
	backward_boost.speed = 0.5f;

	animation = &idle;

	shoot_number = shoot_num;
	initial_y = y;
	increment_y = 0.0f;

	
	score_points = 130;//130
	hits_life = 21.0f;// 21.0f
	down = true;
	
	collider = App->collision->AddCollider({ 0, 0, 71, 53 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void GreenShooter_Spaceship::Move() {
	increment_y = (position.y - initial_y);

	if (lineal_shoot) {	//shots 5 bullets sequentially
		Shot(color_rotatory_shot, App->player->position, position);
		Shot(color_rotatory_shot, App->player->position, {position.x+ 53, position.y+20  });
		
		lineal_shoot = false;
	}

	if (disperse_shoot) {//shots 8 bullets at the same time
		ShotVector(color_rotatory_shot, {2, 1}, { position.x + 35, position.y + 26 });
		ShotVector(color_rotatory_shot, { -1, 1 }, { position.x + 35, position.y + 26 });
		ShotVector(color_rotatory_shot, { 3, 0 }, { position.x + 35, position.y + 26 });
		ShotVector(color_rotatory_shot, { -3, 0 }, { position.x + 35, position.y + 26 });
		ShotVector(color_rotatory_shot, { 1,-3 }, { position.x + 35, position.y + 26 });
		ShotVector(color_rotatory_shot, { -1, -3 }, { position.x + 35, position.y + 26 });
		ShotVector(color_rotatory_shot, { 3, -2 },  { position.x + 35, position.y + 26 });
		ShotVector(color_rotatory_shot, { -3, -2 },  { position.x + 35, position.y + 26 });
		

		

		disperse_shoot = false;
	}


	if (down) {
		if (increment_y < 55) {
			speed = 0.3f;
			if ((increment_y >= 40) && (shoot_number == 3)) {//lineal shot
				lineal_shoot = true;
				shoot_number--;
			}
		}

		else if (increment_y > 55 && increment_y < 120) {
			speed = 1.0f;			
			animation = &boost;
			if (position.x < App->player->position.x)position.x++;
			else if (position.x > App->player->position.x)position.x--;
		}

		else if (increment_y >= 120) {
			
			down = false;
			speed = -2.0f;
			animation = &backward_idle;
		}
	}
	else
	{
		if (increment_y < 120 && increment_y>-200) {
			speed = -2.3f;
			if ((increment_y <= -80) && (shoot_number == 2)) {//disperse shot
				disperse_shoot = true;
				shoot_number--;

			}
		}
		else if (increment_y < -200) {
			speed = -3.0f;
			animation = &backward_boost;
			if ((increment_y <= -300) && (shoot_number == 1)) {//disperse shot
				disperse_shoot = true;
				shoot_number--;
			}

		}
	}
	position.y += speed;
	collider->SetPos(position.x, position.y);
	
}

void GreenShooter_Spaceship::Shot(Particle& shot, iPoint aim_position, fPoint shot_initial_pos) {

	shot.speed = { 0,0 };

	if ((int)shot_initial_pos.y < aim_position.y) {//down 
		if (aim_position.y - shot_initial_pos.y < 75)
			shot.speed.y = 1.0f;
		else if ((aim_position.y - shot_initial_pos.y > 75) && (aim_position.y - shot_initial_pos.y < 150))
			shot.speed.y = 3.0f;
		else if (aim_position.y - shot_initial_pos.y > 150)
			shot.speed.y = 5.0f;
	}


	else if ((int)shot_initial_pos.y > aim_position.y) {//up
		if (aim_position.y - shot_initial_pos.y < 75)
			shot.speed.y = -3.0f;
		else if ((aim_position.y - shot_initial_pos.y > 75) && (aim_position.y - shot_initial_pos.y < 150))
			shot.speed.y = -5.0f;
		else if (aim_position.y - shot_initial_pos.y > 150)
			shot.speed.y = -7.0f;
	}


	if ((int)shot_initial_pos.x+35 < aim_position.x) {//right
		if (aim_position.x - shot_initial_pos.x < 75)
			shot.speed.x = 1.0f;
		else if ((aim_position.x - shot_initial_pos.x > 75) && (aim_position.x - shot_initial_pos.x < 150))
			shot.speed.x = 3.0f;
		else if (aim_position.x - shot_initial_pos.x > 150)
			shot.speed.x = 5.0f;
	}
	if ((int)shot_initial_pos.x-35 > aim_position.x) {//left
		if (aim_position.x - shot_initial_pos.x < 75)
			shot.speed.x = -1.0f;
		else if ((aim_position.x - shot_initial_pos.x > 75) && (aim_position.x - shot_initial_pos.x < 150))
			shot.speed.x = -3.0f;
		else if (aim_position.x - shot_initial_pos.x > 150)
			shot.speed.x = -5.0f;
	}
	if ((aim_position.x < (int)shot_initial_pos.x + 35) && (aim_position.x > (int)shot_initial_pos.x - 35)) {// in front of the greenspaceship (shoots completely vertical)
		shot.speed.x = 0;
	}



	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT);

	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT, 30);
	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT, 60);
	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y , COLLIDER_ENEMY_SHOT, 90);
	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT, 120);
	

}


void GreenShooter_Spaceship::ShotVector(Particle& shot, iPoint velocity_vector, fPoint shot_initial_pos) {
	
	shot.speed.x = velocity_vector.x;
	shot.speed.y = velocity_vector.y;
	App->particles->AddParticle(shot, shot_initial_pos.x, shot_initial_pos.y, COLLIDER_ENEMY_SHOT);
	
}


void GreenShooter_Spaceship::OnCollision(Collider*collider, int num_enemy){

	if (collider->type == COLLIDER_PLAYER_SHOT) {
		hits_life-= App->player->hit_dmg;
		
	}
	else if ((App->player2->IsEnabled()) && (collider->type == COLLIDER_PLAYER2_SHOT)) {
		hits_life -= App->player2->hit_dmg;		
	}
	else if (collider->type == COLLIDER_BOMB|| collider->type == COLLIDER_BOMB2) {
		hits_life -= App->player->bomb_dmg;
		
	}
	if (hits_life <= 0) {
		Dead(collider, num_enemy);
		}

}

void GreenShooter_Spaceship::Dead(Collider* shooter, int num_enemy) {
	if (shooter->type == COLLIDER_PLAYER_SHOT || shooter->type == COLLIDER_BOMB) {
		App->player->score += score_points;
	}
	else if (shooter->type == COLLIDER_PLAYER2_SHOT || shooter->type == COLLIDER_BOMB2) {
		App->player2->score += score_points;
	}

	App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_EXPLOSION);
	fx_shoot = App->audio->Load_Fx("Assets/Audio/Fx_BigSpaceship_Explosion.wav");
	if (!fx_shoot) {
		LOG("Error loading shoot's fx: %s", Mix_GetError)
	}
	App->audio->Play_Fx(fx_shoot);
	delete App->enemies->enemies[num_enemy];
	App->enemies->enemies[num_enemy] = nullptr;

}