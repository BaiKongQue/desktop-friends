#pragma once
#ifndef DF_GAME
#define	DF_GAME

#include <SDL_events.h>
#include <vector>
#include <utility>
#include <string>

#include "../Display/Display.h"
#include "../Entity/Entity.h"

class Entity;

typedef std::vector<Entity *> Entities;

class Game {
public:
	static Display *display;
	static TTF_Font *font;
	static Entities *entities;
private:
	static bool running;
	Uint64 lastTick;
	Uint64 currTick;
	double deltaTime;
public:
	Game();
	~Game();
	void Run();
	static void Stop();
private:
	void Events(SDL_Event &event);
	void Update();
	void Render();
	void Cleanup();
	void Tick();
};


#endif // !DF_GAME
