#pragma once
#ifndef DF_GAME
#define	DF_GAME

#include "../Display/Display.h"
#include <SDL.h>
#include <SDL_events.h>

class Game {
public:
	static Display *display;

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
