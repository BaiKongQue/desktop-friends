#include "Entity.h"

Entity::Entity(const std::string &image, SDL_Rect & rect) :
	state(EntityState::idle),
	type(EntityType::object),
	pos(0.0f,0.0f),
	box(rect)
{
	Game::entities->push_back(this);
}

Entity::~Entity() {
	SDL_DestroyTexture(this->sprite);
	this->sprite = nullptr;
}

void Entity::Update() {}

void Entity::Render(float delta, int frame) {

}
