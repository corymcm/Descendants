#include "stdafx.h"
#include "Player.h"

GameObject::Player::Player(std::string texturePath, SDL_Renderer* renderer, SDL_Rect* position, SDL_Rect* destination)
	: GameObject(texturePath, renderer, position)
{
	if (destination != nullptr)
	{
		_dest_x = destination->x;
		_dest_y = destination->y;
		_dest_w = destination->w;
		_dest_h = destination->h;
	}
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
				_dest_y -= 1;
				break;
			case SDLK_s:
				_dest_y += 1;
				break;
			case SDLK_a:
				_dest_x -= 1;
				break;
			case SDLK_d:
				_dest_x += 1;
				break;
			default:
				break;
		}
	}
}

void GameObject::Player::Render(SDL_Renderer* renderer)
{
	if (_requiresLoad)
		_texture = LoadTexture(_texturePath, renderer);

	SDL_RenderCopy(renderer, _texture, GetPosition(), GetDestination());
}
