#include "Entity.h"

Entity::Entity(const char *image, SDL_Rect rect) :
	sprite(new Sprite(image, 32, 32, this->destRect)),
	type(EntityType::object),
	destRect(new SDL_Rect({ 0,0,32,32 })),
	velocityX(0.0f),
	velocityY(0.0f),
	acceleration(30.0f),
	maxSpeed(150.0f),
	gravity(9.8f),
	lookDirection(1),
	isMoving(false),
	isSelected(true),
	boundaryY(Display::GetScreenHeight()),
	boundaryX(Display::GetScreenWidth()),
	flip(SDL_FLIP_NONE),
	moveKeysActive(0)
{
	this->SetScale(5);
	Game::entities->push_back(this);
}

Entity::~Entity() {
	delete this->sprite;
	this->sprite = nullptr;
}

void Entity::Update(float delta) {
	this->sprite->Update(delta);

	// handle gravity
	if (this->GetBottom() != Display::GetScreenHeight()) {
		this->sprite->ChangeState(0);
		this->velocityY += this->gravity;
		this->destRect->y = int(this->GetY() + this->velocityY * delta);
	} else {
		this->velocityY = 0;
	}

	this->MoveUpdate(delta);
}

void Entity::Render(float delta) {
	Display::Draw(
		this->sprite->GetTexture(),
		this->destRect,
		&this->sprite->GetSrcRect(),
		this->flip
	);

	// draw dest rect
	SDL_SetRenderDrawColor(Display::renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(Display::renderer, this->destRect);

	// draw baseline
	SDL_Rect a = *this->destRect;
	a.x = this->GetX();
	a.y = this->GetBottom();
	a.h = 0;
	SDL_SetRenderDrawColor(Display::renderer, 0, 0, 255, 255);
	SDL_RenderDrawRect(Display::renderer, &a);

	// draw hitbox
	SDL_Rect b = this->sprite->GetHitbox();
	b.x = this->GetX();
	b.y = this->GetY();
	SDL_SetRenderDrawColor(Display::renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(Display::renderer, &b);

	// draw boundaries
	SDL_SetRenderDrawColor(Display::renderer, 255, 0, 254, 255);
	SDL_RenderDrawLine(Display::renderer, Display::GetScreenWidth(), 0, Display::GetScreenWidth(), Display::GetScreenHeight());
	SDL_RenderDrawLine(Display::renderer, 0, Display::GetScreenHeight(), Display::GetScreenWidth(), Display::GetScreenHeight());
}


void Entity::SetScale(int scale) {
	if (scale <= 0) scale = 1;
	SDL_Rect srcRect = this->sprite->GetSrcRect();
	this->scale = scale;
	this->destRect->w = srcRect.w * scale;
	this->destRect->h = srcRect.h * scale;
}

void Entity::Move(int direction) {
	this->moveKeysActive++;
	if (!this->isSelected) return;
	this->isMoving = true;
	this->sprite->ChangeState(1);

	this->velocityX = 0;
	this->lookDirection = (direction != 0) ? (direction >= 1 ? 1 : -1) : 0;
	this->flip = (this->lookDirection == 1) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
	//printf("move %d\n", direction);
}

void Entity::StopMoving() {
	this->moveKeysActive--;
	if (!this->isSelected || this->moveKeysActive > 0) return;
	this->sprite->ChangeState(0);
	this->isMoving = false;
}

void Entity::Jump() {
	if (this->GetBottom() == Display::GetScreenHeight()) {
		this->velocityY = -200;
		this->destRect->y = int(this->GetY() + this->velocityY * 0.016f);
		this->sprite->ChangeState(0);
	}
}

int Entity::GetX() { return this->destRect->x + this->sprite->GetHitbox().x; }
int Entity::GetY() { return this->destRect->y + this->sprite->GetHitbox().y; }
int Entity::GetBottom() { return (this->destRect->y + this->destRect->h) - this->sprite->GetBaselineHeightOffset(); }
int Entity::GetTop() { return this->destRect->y; }
int Entity::GetLeft() { return this->destRect->x; }
int Entity::GetRight() { return this->destRect->x + this->destRect->w; }
int Entity::GetBaseline() { return (this->destRect->y + this->destRect->h) - this->sprite->GetBaselineHeightOffset(); }

bool Entity::HasCollision(bool x, bool y) {
	// returns if this entity has a collision with any entity in the Game::entities list
	for (Entity *entity : *Game::entities) {
		//if (entity->GetBottom())
	}
	return false;
}

void Entity::MoveUpdate(float delta) {
	// handle movement
	if (this->isMoving && ((this->lookDirection == 1 && this->GetRight() != Display::GetScreenWidth()) || (this->lookDirection == -1 && this->GetLeft() != 0))) {
		this->sprite->ChangeState(1);
		this->velocityX = std::max(
			std::min(this->velocityX + (this->acceleration * this->lookDirection), this->maxSpeed), 
			-this->maxSpeed
		);
	} else {
		this->sprite->ChangeState(0);
		if (this->velocityX != 0) {
			this->velocityX = (
				(this->lookDirection >= 1 && this->velocityX <= 0)
				|| (this->velocityX >= 0)
			) ? 0 : (this->velocityX - (this->acceleration * this->lookDirection));
		}
	}
	this->destRect->x = int(this->GetX() + (this->velocityX * delta));
	//printf("%f | %f | %d\n", this->velocityX, this->velocityY, this->destRect.x);

	// snap to inside boundaries
	if (this->GetLeft() < 0) {
		this->destRect->x = 0;
	} else if (this->GetRight() > Display::GetScreenWidth()) {
		this->destRect->x = Display::GetScreenWidth() - this->destRect->w;
	}

	if (this->GetBottom() > Display::GetScreenHeight()) {
		this->destRect->y = Display::GetScreenHeight() - this->destRect->h + this->sprite->GetBaselineHeightOffset();
	}
}
