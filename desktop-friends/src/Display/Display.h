#pragma once
#ifndef DF_DISPLAY
#define DF_DISPLAY

#include <SDL.h>
#include <SDL_syswm.h>

class Display {
public:	
	SDL_Renderer *renderer;
	SDL_Window *window;
private:
public:
	Display();
	~Display();
private:
};

#endif // !DF_DISPLAY
