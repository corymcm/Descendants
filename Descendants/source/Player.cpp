#include "stdafx.h"
#include "Player.h"

GameObject::Player::Player(SDL_Texture* texture, SDL_Rect* position, SDL_Rect* destination)
	: GameObject(texture, position),
	_destination(destination)
{

}

GameObject::Player::~Player()
{
	delete _destination;
}

void GameObject::Player::Update(SDL_Event* e)
{
	if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.sym)
		{
			case SDLK_w:
				_destination->y -= 1;
				break;
			case SDLK_s:
				_destination->y += 1;
				break;
			case SDLK_a:
				_destination->x -= 1;
				break;
			case SDLK_d:
				_destination->x += 1;
				break;
			default:
				break;
		}
	}
}

void GameObject::Player::Render(SDL_Renderer * renderer)
{
	SDL_RenderCopy(renderer, _texture, _position, _destination);
}