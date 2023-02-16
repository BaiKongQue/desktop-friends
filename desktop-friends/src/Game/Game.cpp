#include "Game.h"

Display *Game::display = nullptr;
Entities *Game::entities = nullptr;
TTF_Font *Game::font = nullptr;
bool Game::running = false;

Game::Game() {
	Game::display = new Display();
	Game::entities = new Entities();

	Game::entities->push_back(new Entity("MiniFox.png", SDL_Rect{0,0,32,32}));

	// initialize Font
	Game::font = TTF_OpenFont("", 28); // TODO: add
	if (Game::font == nullptr) {
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return;
	}
}

Game::~Game() {
	// free font
	TTF_CloseFont(Game::font);
	Game::font = nullptr;

	delete Game::display;
	Game::display = nullptr;

	for (Entity *entity : *Game::entities) {
		delete entity;
		entity = nullptr;
	}

	delete Game::entities;
	Game::entities = nullptr;
}

void Game::Run() {
	Game::running = true;

	SDL_Event event;
	while (Game::running) {
		this->Tick();
		this->Events(event);
		this->Update();
		this->Render();
	}

	this->Cleanup();
}

void Game::Events(SDL_Event &event) {
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			Game::running = false;
		}
	}
}

void Game::Update() {
	for (Entity *entity : *Game::entities) {
		entity->Update(this->deltaTime);
	}
}

void Game::Render() {
	Display::ClearScreen();

	for (Entity *entity : *Game::entities) {
		entity->Render(this->deltaTime);
	}

	Display::RenderScreen();
}

void Game::Stop() {
	Game::running = false;
}

void Game::Cleanup() {
}

void Game::Tick() {
	this->lastTick = this->currTick;
	this->currTick = SDL_GetPerformanceCounter();
	this->deltaTime = (double)((this->currTick - this->lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());
}
