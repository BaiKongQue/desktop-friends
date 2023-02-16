#include "Display.h"

SDL_Renderer *Display::renderer = nullptr;
SDL_Window *Display::window = nullptr;

Display::Display() {
    // Get resolution of primary monitor
    int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
    int desktopHeight = GetSystemMetrics(SM_CYSCREEN);

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	// initialize Img
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return;
	}

	// initialize ttf
	if (TTF_Init() == -1) {
		printf("SDL_TTF could not initialize! SDL_TTF Error: %s\n", TTF_GetError());
	}

	// initializing window
    this->window = SDL_CreateWindow("SDL Transparent Window",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          desktopWidth, desktopHeight, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP);
	if (this->window == nullptr) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	// initialize renderer
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if (this->renderer == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

    // Set background color to magenta and clear screen
    SDL_SetRenderDrawColor(this->renderer, 255, 0, 255, 255);
    SDL_RenderClear(this->renderer);

    // Add window transparency (Magenta will be see-through)
    // Get window handle (https://stackoverflow.com/a/24118145/3357935)
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);  // Initialize wmInfo
    SDL_GetWindowWMInfo(this->window, &wmInfo);
    HWND hWnd = wmInfo.info.win.window;

    // Change window type to layered (https://stackoverflow.com/a/3970218/3357935)
    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

    // Set transparency color
    SetLayeredWindowAttributes(hWnd, RGB(255,0,255), 0, LWA_COLORKEY);

    // Render the square to the screen
    SDL_RenderPresent(this->renderer);
}

Display::~Display() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
	this->renderer = nullptr;
	this->window = nullptr;

	// Quit SDL Image
	IMG_Quit();

	// Quit SDL
	SDL_Quit();
}

void Display::Draw(SDL_Texture *texture, SDL_Rect *dest, SDL_Rect *src = nullptr, SDL_Renderer *renderer = Display::renderer) {
	if (!texture) {
		printf("Failed rendering image, texture is empty!");
		return;
	}

	SDL_RenderCopy(renderer, texture, src, dest);
}

void Display::DrawText(const char *text, SDL_Rect *dest, TTF_Font *font, SDL_Color color = { 0,0,0 }, SDL_Renderer *renderer = Display::renderer) {
	if (!text || !font) {
		printf("Failed to render text. text or font missing");
		return;
	}

	SDL_Texture *texture = LoadTextTexture(text, font, color);
	SDL_RenderCopy(renderer, texture, nullptr, dest);
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void Display::RenderScreen() {
	SDL_RenderPresent(Display::renderer);
}

void Display::ClearScreen() {
	SDL_RenderClear(Display::renderer);
}

SDL_Texture *Display::LoadImageTexture(const char *src) {
	if (!src)
		return nullptr;

	SDL_Surface *tempSurface = IMG_Load(src);
	if (!tempSurface)
		return nullptr;

	SDL_Texture *newTexture = SDL_CreateTextureFromSurface(Display::renderer, tempSurface);

	SDL_FreeSurface(tempSurface);
	tempSurface = nullptr;

	if (!newTexture)
		return nullptr;

	return newTexture;
}

SDL_Texture *Display::LoadTextTexture(const char *text, TTF_Font *font, SDL_Color textColor = { 0,0,0 }) {
	if (!text || !font)
		return nullptr;

	SDL_Surface *tempSurface = TTF_RenderText_Blended(font, text, textColor);
	if (!tempSurface)
		return nullptr;

	SDL_Texture *msgTexture = SDL_CreateTextureFromSurface(Display::renderer, tempSurface);
	if (!msgTexture)
		return nullptr;

	SDL_FreeSurface(tempSurface);
	tempSurface = nullptr;

	return msgTexture;
}