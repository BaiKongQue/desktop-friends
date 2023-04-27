#pragma once
#ifndef DF_SPRITE_H
#define DF_SPRITE_H

#include "../../Display/Display.h"
#include "../Animation/Animation.h"
#include <vector>
#include <string>

typedef std::vector<std::vector<SDL_Rect>> HitBoxes;
typedef std::pair<int, int> Pos;

class Sprite {
public:
private:
	SDL_Texture *texture;
	Animation *animation;
	SDL_Rect srcRect;
	SDL_Rect *entityRect;
	Pos origin;
	HitBoxes hitBoxes;
	int baselineHeightOffsets;
	int state;
	int nextState;
public:
	Sprite(const char *image, int width, int height, SDL_Rect *entityRect);
	~Sprite();

	void Update(float delta);
	void ChangeState(int state);

	// getters
	SDL_Texture *GetTexture();
	SDL_Rect &GetHitbox();
	SDL_Rect &GetSrcRect();
	Pos &GetOrigin();
	int GetOriginX();
	int GetOriginY();
	int GetBaselineHeightOffset();
	int GetState();

private:
};

#endif // !DF_SPRITE_H
