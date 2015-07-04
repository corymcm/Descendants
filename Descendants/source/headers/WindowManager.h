#pragma once

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

namespace WindowManger
{
	class WindowManger
	{
	private:
		SDL_Window* _window;
	public:
		WindowManger(char* title, int posx, int posy, int width, int height);
		SDL_Renderer* CreateRenderer();

		~WindowManger();
	};
}
#endif // WINDOWMANAGER_H