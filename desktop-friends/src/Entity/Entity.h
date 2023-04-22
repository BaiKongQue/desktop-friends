#pragma once
#ifndef DF_ENTITY_H
#define DF_ENTITY_H

#include "../Game/Game.h"
#include "Sprite/Sprite.h"

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
protected:
	Sprite *sprite;
	EntityType type;
	SDL_Rect destRect;
	float velocityX;
	float velocityY;
	float acceleration;
	float maxSpeed;
	float gravity;
	int scale;
	int lookDirection;
	bool isMoving;
	bool isSelected;
private:
	const int boundaryX;
	const int boundaryY;
	SDL_RendererFlip flip;
	int moveKeysActive;
public:
	Entity(const char *image, SDL_Rect rect);
	~Entity();
	virtual void Update(float delta);
	virtual void Render(float delta);

	void SetScale(int scale);

	void Move(int direction);
	void StopMoving();
	void Jump();

	int GetX();
	int GetY();
	int GetBottom();
	int GetTop();
	int GetLeft();
	int GetRight();
	int GetBaseline();
protected:
	bool HasCollision(bool x = true, bool y = true);
private:
	void MoveUpdate(float delta);
};



#endif // !DF_ENTITY_H
