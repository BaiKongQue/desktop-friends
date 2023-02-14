#pragma once
#ifndef DF_GAME
#define	DF_GAME

#include <SDL.h>
#include <SDL_events.h>
#include "../Display/Display.h"
#include "../Definitions/types.def.h"

typedef

class Game {
public:
	static Display *display;
	static Entities *entities;
private:
	bool running;
public:
	Game();
	~Game();
	void Run();
private:
	void Events(SDL_Event &event);
	void Update();
	void Render();
	void Cleanup();
};


#endif // !DF_GAME
