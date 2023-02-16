#include "Entity.h"

Entity::Entity(const char *image, SDL_Rect rect) :
	state(EntityState::idle),
	type(EntityType::object),
	pos(0.0f,0.0f),
	box(rect)
{
	Game::entities->push_back(this);
	this->sprite = Display::LoadImageTexture((std::string("assets/entities/animals") + image).c_str());
}

Entity::~Entity() {
	SDL_DestroyTexture(this->sprite);
	this->sprite = nullptr;
}

void Entity::Update(double delta) {}

void Entity::Render(double delta) {}

