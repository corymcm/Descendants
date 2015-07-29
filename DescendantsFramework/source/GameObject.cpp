#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject::GameObject()
{

}

GameObject::GameObject::GameObject(std::string textureName, Rect* source, Rect* destination)
{
	if (source != nullptr)
	{
		SourceRect.x = source->x;
		SourceRect.y = source->y;
		SourceRect.w = source->w;
		SourceRect.h = source->h;
	}

	if (destination != nullptr)
	{
		DestRect.x = destination->x;
		DestRect.y = destination->y;
		DestRect.w = destination->w;
		DestRect.h = destination->h;
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