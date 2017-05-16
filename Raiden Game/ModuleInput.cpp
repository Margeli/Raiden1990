#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
	for (uint i = 0; i < MAX_BUTTONS; ++i)
		gamepad[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	if (SDL_Init(SDL_INIT_JOYSTICK)< 0) {
		LOG("SDL_INIT_JOYSTICK could not initialize , SDL Error: %s\n", SDL_GetError() )
	}
	if (SDL_NumJoysticks() < 1)	{
		LOG(" No joysticks connected!\n");
	}
	else{
		//Load joystick
		controller = SDL_GameControllerOpen(controller_index);
		use_controller = true;
		if (controller == NULL){
			LOG(" Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			use_controller = false;
		}
	}
	


	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	Uint8 buttons[MAX_BUTTONS];

	buttons[0] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
	buttons[1] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	buttons[2] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	buttons[3] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	buttons[4] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A);
	buttons[5] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
	buttons[6] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_START);
	buttons[7] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_LEFTSTICK);
	buttons[8] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);


	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}
	for (int i = 0; i < MAX_BUTTONS; ++i)
	{
		if (buttons[i] == 1)
		{
			if (gamepad[i] == KEY_IDLE)
				gamepad[i] = KEY_DOWN;
			else
				gamepad[i] = KEY_REPEAT;
		}
		else
		{
			if (gamepad[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				gamepad[i] = KEY_UP;
			else
				gamepad[i] = KEY_IDLE;
		}
	}
	if (keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;





	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	//Close game controller
	SDL_GameControllerClose(controller);
	controller = NULL;
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}