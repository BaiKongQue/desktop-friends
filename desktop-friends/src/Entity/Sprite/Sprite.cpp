#include "Sprite.h"

Sprite::Sprite(const char *image, int width, int height) :
	texture(nullptr),
	animation(nullptr),
	srcRect({ 0,0,32,32 }),
	origin({32/2,height - 4}),
	hitBoxes(),
	baselineHeightOffsets(4),
	state(0),
	nextState(-1)
{
	this->texture = Display::LoadImageTexture((std::string("assets/entities/animals/") + image).c_str());
	if (this->texture == nullptr) {
		printf("Failed to load image: %s.", (std::string("assets/entities/animals/") + image).c_str());
		exit(1);
	}

	this->animation = new Animation(4, 0.4f);

	std::vector<SDL_Rect> hitBox;
	hitBox.push_back({ 0, 0, width, height });
	this->hitBoxes.push_back(hitBox);
}

Sprite::~Sprite() {
	SDL_DestroyTexture(this->texture);
	this->texture = nullptr;

	delete this->animation;
	this->animation = nullptr;
}

void Sprite::Update(float delta) {
	this->animation->Update(delta, this->srcRect);
}

void Sprite::ChangeState(int state) {
	if (this->state == state) return;
	this->nextState = state;
	this->state = this->nextState;

	this->srcRect.y = this->srcRect.h * this->nextState;

	this->animation->SetFrame(0);
	this->srcRect.x = this->srcRect.w * this->animation->GetFrame();
}

SDL_Texture *Sprite::GetTexture() { return this->texture; }
SDL_Rect &Sprite::GetHitbox() {
	// throw error if the state is larger than the number in hitbox
	if (this->state >= this->hitBoxes.size()) {
		printf("Sprite::GetHitbox() - state is larger than the number in hitbox. (%d/%d)", this->state, this->hitBoxes.size());
		exit(1);
	}

	// throw error if frame is larger than hitbox[this->state]
	if (this->animation->GetFrame() >= this->hitBoxes[this->state].size()) {
		printf("Error: current frame is larger than the number of hitboxs in the current state. (%d/%d)", this->animation->GetFrame(), this->hitBoxes[this->state].size());
		exit(1);
	}

	return this->hitBoxes[this->state][this->animation->GetFrame()];
}
SDL_Rect &Sprite::GetSrcRect() { return this->srcRect; }
Pos &Sprite::GetOrigin() { return this->origin; }
int Sprite::GetOriginX() { return this->origin.first; }
int Sprite::GetOriginY() { return this->origin.second; }
int Sprite::GetBaselineHeightOffset() { return this->baselineHeightOffsets; }
int Sprite::GetState() { return this->state; }