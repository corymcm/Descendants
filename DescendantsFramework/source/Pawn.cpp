#include "stdafx.h"
#include "Pawn.h"

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(Framework::Pawn, "Pawn");

Framework::Pawn::Pawn(std::string texturePath, Rect* source, Rect* destination)
	: GameObject(texturePath, source, destination)
{

}

Framework::Pawn::~Pawn()
{

}

void Framework::Pawn::Update()
{

}
