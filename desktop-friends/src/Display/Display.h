#pragma once
#ifndef DF_DISPLAY
#define DF_DISPLAY

#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstdio>

class Display {
public:	
	static SDL_Renderer *renderer;
	static SDL_Window *window;
private:
public:
	Display();
	~Display();
	static void Draw(SDL_Texture *, SDL_Rect *, SDL_Rect *, SDL_Renderer *);
	static void DrawText(const char *, SDL_Rect *, TTF_Font *, SDL_Color, SDL_Renderer *);
	static void RenderScreen();
	static void ClearScreen();
	static SDL_Texture *LoadImageTexture(const char *);
	static SDL_Texture *LoadTextTexture(const char *, TTF_Font *, SDL_Color);
private:
};





#endif // !DF_DISPLAY
