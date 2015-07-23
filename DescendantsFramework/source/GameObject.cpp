#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject::GameObject()
{

}

GameObject::GameObject::GameObject(std::string textureName, SDL_Rect* source, SDL_Rect* destination)
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

	_textureName = textureName;
}

GameObject::GameObject::~GameObject()
{
}

void GameObject::GameObject::Update(SDL_Event* e)
{
	DESCENDANT_UNUSED(e);
}