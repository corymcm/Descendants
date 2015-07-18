#include "stdafx.h"
#include "Pawn.h"

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(GameObject::Pawn, "Pawn");

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

