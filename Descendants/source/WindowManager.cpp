#include "stdafx.h"
#include "WindowManager.h"

WindowManger::WindowManger::WindowManger(char* title, int posx, int posy, int width, int height)
	:_window(nullptr)
{
	_window  = SDL_CreateWindow(title, posx, posy, width, height, SDL_WINDOW_SHOWN);
	ASSERT(_window);
}

WindowManger::WindowManger::~WindowManger()
{
	if (_window != nullptr)
		SDL_DestroyWindow(_window);
}

SDL_Renderer* WindowManger::WindowManger::CreateRenderer()
{
	ASSERT(_window);

	return SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}