#include "stdafx.h"
#include "Player.h"

GameObject::Player::Player(std::string texturePath, SDL_Renderer* renderer, SDL_Rect* position, SDL_Rect* destination)
	: GameObject(texturePath, renderer, position, destination)
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
				dest_y -= 1;
				break;
			case SDLK_s:
				dest_y += 1;
				break;
			case SDLK_a:
				dest_x -= 1;
				break;
			case SDLK_d:
				dest_x += 1;
				break;
			default:
				break;
		}
	}
}

