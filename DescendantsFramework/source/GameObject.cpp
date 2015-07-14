#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject::GameObject(std::string texturePath, SDL_Renderer* renderer, int posx, int posy, int width, int height)
	:_texture(nullptr)
{
	pos_x = posx;
	pos_y = posy;
	pos_w = width;
	pos_h = height;

	_texture = LoadTexture(texturePath, renderer);
	_texturePath = texturePath;
	_requiresLoad = false;
}

GameObject::GameObject::GameObject()
	:_texture(nullptr)
{
}

GameObject::GameObject::GameObject(std::string texturePath, SDL_Renderer* renderer, SDL_Rect* position)
	:_texture(nullptr)
{
	if (position != nullptr)
	{
		pos_x = position->x;
		pos_y = position->y;
		pos_w = position->w;
		pos_h = position->h;
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
		_texture = LoadTexture(_texturePath, renderer);

	SDL_RenderCopy(renderer, _texture, GetPosition(), NULL);
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