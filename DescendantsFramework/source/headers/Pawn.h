#pragma once

#ifndef PAWN_H
#define PAWN_H

#include "GameObject.h"

namespace GameObject
{
	class DESCENDANT_EXPORT Pawn : public GameObject
	{
	private:
		SDL_Rect* _destination;

	public:
		Pawn(SDL_Texture* texture, SDL_Rect* position, SDL_Rect* destination);
		virtual ~Pawn();

		virtual void Update(SDL_Event* e);
		virtual void Render(SDL_Renderer* renderer);
	};
}

#endif // PAWN_H