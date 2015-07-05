#pragma once

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <vector>

namespace WindowManger
{
	class WindowManger
	{
	private:
		SDL_Window* _window;
		SDL_Renderer* _renderer;
		std::vector<SDL_Texture*> Textures;

		SDL_Renderer* CreateRenderer();
		SDL_Surface* LoadBitmap(const char* path);

	public:
		WindowManger(char* title, int posx, int posy, int width, int height);
		~WindowManger();

		void Update();
		bool LoadTexture(const char* path);
	};
}
#endif // WINDOWMANAGER_H