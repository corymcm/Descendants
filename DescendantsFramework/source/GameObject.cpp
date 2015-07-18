#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject::GameObject()
	:_texture(nullptr)
{

}

GameObject::GameObject::GameObject(std::string texturePath, SDL_Renderer* renderer, SDL_Rect* source, SDL_Rect* destination)
	:_texture(nullptr)
{
	if (source != nullptr)
	{
		src_x = source->x;
		src_y = source->y;
		src_w = source->w;
		src_h = source->h;
	}

	if (destination != nullptr)
	{
		dest_x = destination->x;
		dest_y = destination->y;
		dest_w = destination->w;
		dest_h = destination->h;
	}

	_texture = LoadTexture(texturePath, renderer);
	_texturePath = texturePath;
	_requiresLoad = false;
}

GameObject::GameObject::~GameObject()
{
	SDL_DestroyTexture(_texture);
}

void GameObject::GameObject::Update(SDL_Event* e)
{
	DESCENDANT_UNUSED(e);
}

void GameObject::GameObject::Render(SDL_Renderer* renderer)
{
	if (_requiresLoad)
	{
		_texture = LoadTexture(_texturePath, renderer);
		_requiresLoad = false;
	}
	SDL_RenderCopy(renderer, _texture, GetPosition(), GetDestination());
}

SDL_Surface* GameObject::GameObject::LoadBitmap(const char* path)
{
	SDL_Surface* bmp = SDL_LoadBMP(path);
	if (bmp == nullptr)
	{
		LogError("SDL_LoadBMP Error: ");
		return nullptr;
	}
	return bmp;
}

SDL_Texture* GameObject::GameObject::LoadTexture(std::string texturePath, SDL_Renderer* renderer)
{
	SDL_Surface* bmp = LoadBitmap(texturePath.c_str());

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr)
	{
		LogError("SDL_CreateTextureFromSurface Error: ");

		return nullptr;
	}

	return tex;
}