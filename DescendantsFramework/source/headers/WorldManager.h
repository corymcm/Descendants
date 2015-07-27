#pragma once

#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <vector>
#include "World.h"
#include "IRenderer.h"
#include "ISoundManager.h"

namespace WorldManager
{
	class WorldManager
	{
	private:
		Framework::ISoundManager* _soundManager;
		World::World* _curretWorld;
		std::string _worldPath;
		std::string _texturePath;

	public:
		DESCENDANT_EXPORT inline World::World* GetCurrentWorld() { return _curretWorld; }

		DESCENDANT_EXPORT WorldManager(std::string resourcePath, Framework::ISoundManager* soundManager);
		DESCENDANT_EXPORT WorldManager(std::string resourcePath, Framework::ISoundManager* soundManager, World::World* world);
		DESCENDANT_EXPORT ~WorldManager();

		DESCENDANT_EXPORT void UpdateWorld(SDL_Event* e);
		DESCENDANT_EXPORT void RenderWorld(Framework::IRenderer* renderer);
		DESCENDANT_EXPORT void LoadWorld(std::string worldName);
		DESCENDANT_EXPORT void SaveWorld();
	};
}

#endif // WORLDMANAGER_H