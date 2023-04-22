#pragma once
#ifndef DF_DISPLAY_H
#define DF_DISPLAY_H

#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstdio>

class Display {
public:	
	static SDL_Renderer *renderer;
	static SDL_Window *window;
	static SDL_Surface *windowSurface;
private:
public:
	Display();
	~Display();
	static void Draw(SDL_Texture *texture, SDL_Rect *dest, SDL_Rect *src = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Renderer *renderer = Display::renderer);
	static void DrawText(const char *text, SDL_Rect *dest, TTF_Font *font, SDL_Color color = { 0,0,0 }, SDL_Renderer *renderer = Display::renderer);
	static void RenderScreen();
	static void ClearScreen();
	static SDL_Texture *LoadImageTexture(const char *src);
	static SDL_Texture *LoadTextTexture(const char *text, TTF_Font *font, SDL_Color textColor = { 0,0,0 });
	static int GetScreenWidth();
	static int GetScreenHeight();
private:
};





#endif // !DF_DISPLAY_H
