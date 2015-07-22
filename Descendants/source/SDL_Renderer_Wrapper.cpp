#include "stdafx.h"
#include "SDL_Renderer_Wrapper.h"

Renderers::SDL_Renderer_Wrapper::SDL_Renderer_Wrapper(SDL_Renderer* renderer)
{
	_renderer = renderer;
}

Renderers::SDL_Renderer_Wrapper::~SDL_Renderer_Wrapper()
{
	SDL_DestroyRenderer(_renderer);
}

void Renderers::SDL_Renderer_Wrapper::Render(GameObject::GameObject* obj, std::string texturePath)
{
	if (obj->RequiresLoad)
		obj->SetTexture(texturePath, _renderer);

	SDL_RenderCopy(_renderer, obj->GetTexture(), obj->GetSource(), obj->GetDestination());
}

void Renderers::SDL_Renderer_Wrapper::ClearRenderer()
{
	SDL_RenderClear(_renderer);
}

void Renderers::SDL_Renderer_Wrapper::RenderPresent()
{
	SDL_RenderPresent(_renderer);
}

