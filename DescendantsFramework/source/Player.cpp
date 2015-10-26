#include "stdafx.h"
#include "Player.h"

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(Framework::Player, "Player");

Framework::Player::Player(std::string texturePath, Rect* source, Rect* destination, std::string controllerName, int lives)
	: GameObject(texturePath, source, destination),
	_playerController(nullptr),
	_lives(lives),
	ControllerName(controllerName)
{

}

Framework::Player::~Player()
{

}

void Framework::Player::Update()
{
	if (_playerController == nullptr)
	{
		return;
	}
	_playerController->UpdateController(this);
}
