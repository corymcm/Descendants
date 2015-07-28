#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject::GameObject()
{

}

GameObject::GameObject::GameObject(std::string textureName, SDL_Rect* source, SDL_Rect* destination)
{
	if (source != nullptr)
	{
		_sourceRect.x = source->x;
		_sourceRect.y = source->y;
		_sourceRect.w = source->w;
		_sourceRect.h = source->h;
	}

	if (destination != nullptr)
	{
		_destRect.x = destination->x;
		_destRect.y = destination->y;
		_destRect.w = destination->w;
		_destRect.h = destination->h;
	}

	_textureName = textureName;
}

GameObject::GameObject::~GameObject()
{
}

void GameObject::GameObject::Update(SDL_Event* e)
{
	DESCENDANT_UNUSED(e);
}