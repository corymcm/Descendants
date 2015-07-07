#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject::GameObject(SDL_Texture* texture, int posx, int posy, int width, int height)
	:_texture(texture),
	_position(nullptr)
{
	_position = new SDL_Rect();
	_position->x = posx;
	_position->y = posy;
	_position->w = width;
	_position->h = height;
}

GameObject::GameObject::GameObject(SDL_Texture* texture, SDL_Rect* position)
	:_position(position),
	_texture(texture)
{

}

GameObject::GameObject::~GameObject()
{
	SDL_DestroyTexture(_texture);
	delete _position;
}

void GameObject::GameObject::Update()
{

}

void GameObject::GameObject::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, _texture, _position, NULL);
}