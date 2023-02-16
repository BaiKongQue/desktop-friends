#pragma once
#ifndef DF_ENTITY
#define DF_ENTITY

#include "../Game/Game.h"

typedef std::pair<float, float> Pos;

enum EntityState {
	idle = 0,
	walking,
	happy,
	sleep
};

enum EntityType {
	player = 0,
	visitor,
	enemy,
	object
};

class Entity {
public:
	//static Entities *entities;
protected:
	SDL_Texture *sprite;
	EntityState state;
	EntityType type;
	Pos pos;
	SDL_Rect box;
private:
public:
	Entity(const char *, SDL_Rect);
	~Entity();
	virtual void Update(double delta);
	virtual void Render(double delta);
private:
};



#endif // !DF_ENTITY
