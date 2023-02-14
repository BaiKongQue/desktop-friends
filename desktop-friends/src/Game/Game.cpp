#include "Game.h"

Display *Game::display = nullptr;

Game::Game() :
	running(false)
{
	Game::display = new Display();
}

Game::~Game() {
	delete Game::display;
	Game::display = nullptr;
}

void Game::Run() {
	this->running = true;

	SDL_Event event;
	while (this->running) {
		this->Events(event);
		this->Update();
		this->Render();
	}

	this->Cleanup();
}

void Game::Events(SDL_Event &event) {
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			this->running = false;
		}
	}
}

void Game::Update() {
	
}

void Game::Render() {

}

void Game::Cleanup() {
}
