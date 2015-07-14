#include "stdafx.h"
#include "Pawn.h"

GameObject::Pawn::Pawn(std::string texturePath, SDL_Renderer* renderer, SDL_Rect* position, SDL_Rect* destination)
	: GameObject(texturePath, renderer, position)
{
	if (destination != nullptr)
	{
		_dest_x = destination->x;
		_dest_y = destination->y;
		_dest_w = destination->w;
		_dest_h = destination->h;
	}
}

GameObject::Pawn::Pawn()
	: GameObject()
{
}


GameObject::Pawn::~Pawn()
{
}

void GameObject::Pawn::Update(SDL_Event* e)
{
	DESCENDANT_UNUSED(e);
}

void GameObject::Pawn::Render(SDL_Renderer* renderer)
{
	if (_requiresLoad)
		_texture = LoadTexture(_texturePath, renderer);

	SDL_RenderCopy(renderer, _texture, GetPosition(), GetDestination());
}

