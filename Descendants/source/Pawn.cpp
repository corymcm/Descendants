#include "stdafx.h"
#include "Pawn.h"

GameObject::Pawn::Pawn(SDL_Texture* texture, SDL_Rect* position, SDL_Rect* destination)
	: GameObject(texture, position),
	_destination(destination)
{

}

GameObject::Pawn::~Pawn()
{
	delete _destination;
}

void GameObject::Pawn::Update(SDL_Event* e)
{

}

void GameObject::Pawn::Render(SDL_Renderer * renderer)
{
	SDL_RenderCopy(renderer, _texture, _position, _destination);
}