#pragma once

#ifndef SDL_RENDERER_WRAPPER_H
#define SDL_RENDERER_WRAPPER_H

#include "IRenderer.h"

#include "SDL_TextureManager.h"

namespace Renderers
{
	class SDL_Renderer_Wrapper : public Framework::IRenderer
	{
	private:
		SDL_Renderer* _renderer;
		TextureManager::SDL_TextureManager* _textureManager;

		inline SDL_Rect* ConvertToSDL_Rect(Framework::Rect rect)
		{
			if (rect.IsEmpty())
				return nullptr;
			return new SDL_Rect { rect.x, rect.y, rect.w, rect.h };
		}

	public:
		SDL_Renderer_Wrapper(SDL_Renderer* renderer);
		~SDL_Renderer_Wrapper();

		void Render(Framework::GameObject* obj, std::string texturePath) override;
		void ClearRenderer() override;
		void RenderPresent() override;
	};
}

#endif // SDL_RENDERER_WRAPPER_H