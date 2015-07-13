#pragma once

#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <vector>
#include "World.h"

namespace WorldManager
{
	class DESCENDANT_EXPORT WorldManager
	{
	private:
		std::vector<World::World>* _Worlds;


	public:
		WorldManager(SDL_Texture* texture, SDL_Rect* position, SDL_Rect* destination);
		~WorldManager();

		void UpdateWorld(SDL_Event* e);
	};
}

#endif // WORLDMANAGER_H