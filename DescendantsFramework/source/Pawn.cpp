#include "stdafx.h"
#include "Pawn.h"

GameObject::Pawn::Pawn(std::string texturePath, SDL_Renderer* renderer, SDL_Rect* position, SDL_Rect* destination)
	: GameObject(texturePath, renderer, position, destination)
{

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

