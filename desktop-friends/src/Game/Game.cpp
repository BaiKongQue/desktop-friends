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
	Game::font = TTF_OpenFont("assets/fonts/04.ttf", 28);
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
	Uint64 currentTime, elapsedTime, previousTime, frameTime, frequency;
	float deltaTime;

	previousTime = SDL_GetPerformanceCounter();
	frequency = SDL_GetPerformanceFrequency();
	while (Game::running) {
		currentTime = SDL_GetPerformanceCounter();
		elapsedTime = currentTime - previousTime;
		deltaTime = float(elapsedTime) / float(frequency);
		frameTime = static_cast<Uint64>(1000.0 / FRAMES_PER_SECOND);

		while (SDL_PollEvent(&event) != 0) {
			this->Events(event);
		}

		this->Update(deltaTime);
		this->Render(deltaTime);

		elapsedTime = SDL_GetPerformanceCounter() - currentTime;
		//if (elapsedTime < frameTime) {
		//	SDL_Delay(static_cast<Uint32>((frameTime - elapsedTime) * 1000 / frequency));
		//}

		previousTime = currentTime;
	}

	this->Cleanup();
}

void Game::Events(SDL_Event &event) {
	//printf("event pressed %d\n", event.type);
	switch (event.type) {
		case SDL_EventType::SDL_KEYDOWN:
			if (event.key.repeat == 0) {
				switch (event.key.keysym.sym) {
					case SDLK_RIGHT:
						Game::entities->at(0)->Move(1);
						break;
					case SDLK_LEFT:
						Game::entities->at(0)->Move(-1);
						break;
					case SDLK_SPACE:
						Game::entities->at(0)->Jump();
						break;
				}
			}
			break;
		case SDL_EventType::SDL_KEYUP:
			if (event.key.repeat == 0) {
				switch (event.key.keysym.sym) {
					case SDLK_RIGHT:
					case SDLK_LEFT:
						Game::entities->at(0)->StopMoving();
						break;

				}
			}
			break;
		case SDL_EventType::SDL_QUIT:
			Game::running = false;
			break;
	}
}

void Game::Update(float delta) {
	for (Entity *entity : *Game::entities) {
		entity->Update(delta);
	}
}

void Game::Render(float delta) {
	Display::ClearScreen();

	for (Entity *entity : *Game::entities) {
		entity->Render(delta);
	}

	Display::RenderScreen();
}

void Game::Stop() {
	Game::running = false;
}

void Game::Cleanup() {
}