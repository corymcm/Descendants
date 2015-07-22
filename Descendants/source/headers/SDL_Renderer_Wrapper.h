#pragma once

#ifndef SDL_RENDERER_WRAPPER_H
#define SDL_RENDERER_WRAPPER_H


#include "GameObject.h"
#include "Renderer.h"

#include <SDL.h>

namespace Renderers
{
	class SDL_Renderer_Wrapper : public Framework::Renderer
	{
	private:
		SDL_Renderer* _renderer;

	public:
		SDL_Renderer_Wrapper(SDL_Renderer* renderer);
		~SDL_Renderer_Wrapper();

		void Render(GameObject::GameObject* obj, std::string texturePath) override;
		void ClearRenderer() override;
		void RenderPresent() override;
	};
}

#endif // SDL_RENDERER_WRAPPER_H