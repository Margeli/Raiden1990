#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"

#define MAX_KEYS 300
#define JOYSTICK_DEAD_ZONE 8000


enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	SDL_GameController* controller = NULL;

public:
	/*SDL_Event e;

	//Normalized direction
	int xDir = 0;
	int yDir = 0;*/
	bool use_controller = false;
	int controller_index = 0;
};

#endif // __ModuleInput_H__