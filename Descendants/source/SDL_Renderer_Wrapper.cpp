#include "stdafx.h"
#include "SDL_Renderer_Wrapper.h"

Renderers::SDL_Renderer_Wrapper::SDL_Renderer_Wrapper(SDL_Renderer* renderer)
	: _renderer(nullptr),
	_textureManager(nullptr)
{
	_renderer = renderer;
}

Renderers::SDL_Renderer_Wrapper::~SDL_Renderer_Wrapper()
{
	SDL_DestroyRenderer(_renderer);
	delete _textureManager;
}

void Renderers::SDL_Renderer_Wrapper::Render(Framework::GameObject* obj, std::string texturePath)
{
	if (_textureManager == nullptr)
		_textureManager = new TextureManager::SDL_TextureManager(texturePath);

	SDL_Rect* src = ConvertToSDL_Rect(obj->SourceRect);
	SDL_Rect* dst = ConvertToSDL_Rect(obj->DestRect);

	SDL_RenderCopy(_renderer, _textureManager->GetTexture(obj->GetTextureName(), _renderer), src, dst);

	if (src != nullptr)
		delete src;
	if (dst != nullptr)
		delete dst;
}

void Renderers::SDL_Renderer_Wrapper::ClearRenderer()
{
	SDL_RenderClear(_renderer);
}

void Renderers::SDL_Renderer_Wrapper::RenderPresent()
{
	SDL_RenderPresent(_renderer);
}

