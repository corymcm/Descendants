#include "stdafx.h"
#include "WindowManager.h"

WindowManger::WindowManger::WindowManger(char* title, int posx, int posy, int width, int height)
	:_window(nullptr),
	_renderer(nullptr)
{
	_window = SDL_CreateWindow(title, posx, posy, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
	ASSERT(_window);

	_renderer = CreateRenderer();
	ASSERT(_renderer);
}

WindowManger::WindowManger::~WindowManger()
{
	if (_window != nullptr)
		SDL_DestroyWindow(_window);
	if (_window != nullptr)
		SDL_DestroyRenderer(_renderer);
}

SDL_Renderer* WindowManger::WindowManger::CreateRenderer()
{
	ASSERT(_window);

	return SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void WindowManger::WindowManger::Update()
{
	SDL_RenderClear(_renderer);

	for (auto texture : Textures)
	{
		SDL_RenderCopy(_renderer, texture, NULL, NULL);
	}

	SDL_RenderPresent(_renderer);
}

SDL_Surface* WindowManger::WindowManger::LoadBitmap(const char* path)
{
	SDL_Surface* bmp = SDL_LoadBMP(path);
	if (bmp == nullptr)
	{
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		LogError("SDL_LoadBMP Error: ");
		SDL_Quit();
		return nullptr;
	}
	return bmp;
}

bool WindowManger::WindowManger::LoadTexture(const char* path)
{
	SDL_Surface* bmp = LoadBitmap(path);

	SDL_Texture* tex = SDL_CreateTextureFromSurface(_renderer, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr)
	{
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		LogError("SDL_CreateTextureFromSurface Error: ");
		SDL_Quit();
		return false;
	}

	Textures.push_back(tex);

	return true;
}

