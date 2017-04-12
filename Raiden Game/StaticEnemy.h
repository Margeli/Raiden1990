#ifndef __STATIC_ENEMY_H__
#define __STATIC_ENEMY_H__

#include "Enemy.h"

class Static_Enemy : public Enemy
{
private:

	SDL_Rect nave;

public:

	Static_Enemy(int x, int y);

};

#endif // __STATIC_ENEMY_H__