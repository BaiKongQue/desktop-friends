#pragma once
#ifndef DF_GAME_H
#define	DF_GAME_H

#include <SDL_events.h>
#include <vector>
#include <utility>
#include <string>

#include "../Display/Display.h"
#include "../Entity/Entity.h"
#include <algorithm>

class Entity;

typedef std::vector<Entity *> Entities;

#define FRAMES_PER_SECOND 10
#define FRAME_TIME (1000 / FRAMES_PER_SECOND)

class Game {
public:
	static Display *display;
	static TTF_Font *font;
	static Entities *entities;
private:
	static bool running;
public:
	Game();
	~Game();
	void Run();
	static void Stop();
private:
	void Events(SDL_Event &event);
	void Update(float delta);
	void Render(float delta);
	void Cleanup();
};


#endif // !DF_GAME_H
