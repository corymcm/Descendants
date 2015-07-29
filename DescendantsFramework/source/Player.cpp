#include "stdafx.h"
#include "Player.h"

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(GameObject::Player, "Player");

GameObject::Player::Player(std::string texturePath, Rect* position, Rect* destination)
	: GameObject(texturePath, position, destination)
{

}

GameObject::Player::Player()
	:GameObject()
{

}

GameObject::Player::~Player()
{

}

void GameObject::Player::Update(SDL_Event* e)
{
	if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.sym)
		{
			case SDLK_w:
				DestRect.y -= 1;
				break;
			case SDLK_s:
				DestRect.y += 1;
				break;
			case SDLK_a:
				DestRect.x -= 1;
				break;
			case SDLK_d:
				DestRect.x += 1;
				break;
			default:
				break;
		}
	}
}
