#include "stdafx.h"
#include "Player.h"

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(GameObject::Player, "Player");

GameObject::Player::Player(std::string texturePath, Rect* position, Rect* destination, std::string controllerName)
	: GameObject(texturePath, position, destination),
	_playerController(nullptr)
{
	ControllerName = controllerName;
}

GameObject::Player::Player()
	:GameObject(),
	_playerController(nullptr)
{

}

GameObject::Player::~Player()
{

}

void GameObject::Player::Update()
{
	if (_playerController == nullptr)
	{
		return;
	}
	_playerController->UpdateController(this);
}