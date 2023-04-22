#include "Animation.h"

Animation::Animation(int frameCount, float frameDuration) :
	currentFrame(0),
	frameCount(frameCount),
	prevSyncFrame(0),
	frameDuration(frameDuration),
	timeElapsed(0.0f)
{}

Animation::~Animation() {}

void Animation::Update(float delta, SDL_Rect &srcRect) {
	// Update the time since the last frame
	this->timeElapsed += delta;

	// Calculate the current frame index based on the time since the last frame
	int syncFrame = int(this->timeElapsed / this->frameDuration);

	// Check if the current frame index has changed
	if (syncFrame != this->prevSyncFrame) {
		// Check if the current frame index is out of bounds
		if (this->currentFrame + 1 >= this->frameCount) {
			this->currentFrame = 0;
			this->timeElapsed = 0.0f;
			syncFrame = 0;
		} else {
			this->currentFrame++;
		}

		// update srcRect
		srcRect.x = srcRect.w * this->currentFrame;
	}

	//if (this->nextState > -1) {
	//	this->nextState = -1;
	//}

	this->prevSyncFrame = syncFrame;
}

int Animation::GetFrame() { return this->currentFrame; }

void Animation::SetFrame(int frame) { this->currentFrame = frame; }


