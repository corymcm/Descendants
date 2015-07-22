#pragma once

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <vector>
#include "GameObject.h"
#include "SDL_Renderer_Wrapper.h"

namespace WindowManger
{
	class WindowManger
	{
	private:
		int _fps;

		SDL_Window* _window;
		Framework::Renderer* _renderer;
		std::vector<GameObject::GameObject*> _objects;
		
		Framework::Renderer* CreateRenderer();
		void CleanupWindowManger();
		void HandleError(const char* message);

		inline int GetMinimumFrameTime() { return 1000 / _fps; }

	public:
		WindowManger(char* title, int posx, int posy, int width, int height);
		~WindowManger();

		void Update(SDL_Event* e);
		void Render();
		void AddGameObject(GameObject::GameObject* gameObjects);

		inline Framework::Renderer* GetRenderer() { return _renderer; }
		inline int GetFPS(){ return _fps; }
		inline void SetFPS(const int fps) { _fps = fps; }
	};
}
#endif // WINDOWMANAGER_H