#pragma once

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <vector>
#include "GameObject.h"

namespace WindowManger
{
	class WindowManger
	{
	private:
		int _fps;

		SDL_Window* _window;
		SDL_Renderer* _renderer;
		std::vector<GameObject::GameObject*> _objects;
		
		int GetMinimumFrameTime();
		SDL_Renderer* CreateRenderer();
		SDL_Surface* LoadBitmap(const char* path);



	public:
		WindowManger(char* title, int posx, int posy, int width, int height);
		~WindowManger();

		int GetFPS();
		void SetFPS(const int fps);
		void Update();
		SDL_Texture* LoadTexture(const char* path);
		void AddGameObject(GameObject::GameObject* gameObjects);
	};
}
#endif // WINDOWMANAGER_H