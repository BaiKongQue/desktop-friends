#pragma once
#ifndef DF_ENTITY
#define DF_ENTITY

#include "../Game/Game.h"
#include <SDL_image.h>

class Entity {
public:
protected:
	SDL_Texture *sprite;
	EntityState state;
	EntityType type;
	Pos pos;
	SDL_Rect box;
private:
public:
	Entity(const std::string &image, SDL_Rect &rect);
	~Entity();
	virtual void Update();
	virtual void Render(float delta, int frame);
private:
};

#endif // !DF_ENTITY
