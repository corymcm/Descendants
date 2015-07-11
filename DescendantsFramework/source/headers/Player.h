#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

namespace GameObject
{
	class Player : public GameObject
	{
	private:
		SDL_Rect* _destination;

	public:
		Player(SDL_Texture* texture, SDL_Rect* position, SDL_Rect* destination);
		virtual ~Player();

		virtual void Update(SDL_Event* e);
		virtual void Render(SDL_Renderer* renderer);
	};
}

#endif // PLAYER_H