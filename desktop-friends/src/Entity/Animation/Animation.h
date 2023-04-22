#pragma once
#ifndef DF_ANIMATION_H
#define DF_ANIMATION_H

#include <SDL.h>
#include <cstdio>

class Animation {
public:
private:
	int currentFrame;
	int frameCount;
	int prevSyncFrame;

	float frameDuration;
	float timeElapsed;
public:
	Animation(int frameCount, float frameDuration);
	~Animation();
	void Update(float delta, SDL_Rect &srcRect);

	// getters
	int GetFrame();
	
	void SetFrame(int frame);
private:
};

#endif // !DF_ANIMATION_H
