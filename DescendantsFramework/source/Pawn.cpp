#include "stdafx.h"
#include "Pawn.h"

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(GameObject::Pawn, "Pawn");

GameObject::Pawn::Pawn(std::string texturePath, Rect* position, Rect* destination)
	: GameObject(texturePath, position, destination)
{

}

GameObject::Pawn::Pawn()
	: GameObject()
{

}

GameObject::Pawn::~Pawn()
{

}

void GameObject::Pawn::Update()
{

}

