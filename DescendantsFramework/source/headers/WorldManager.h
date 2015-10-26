#pragma once

#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <vector>
#include <unordered_map>

#include "World.h"
#include "IRenderer.h"
#include "ISoundManager.h"

namespace WorldManager
{
	class WorldManager
	{
	public:

		DESCENDANT_EXPORT WorldManager(std::string resourcePath, Framework::ISoundManager* soundManager);
		DESCENDANT_EXPORT WorldManager(std::string resourcePath, Framework::ISoundManager* soundManager, Framework::World* world);
		DESCENDANT_EXPORT ~WorldManager();

		DESCENDANT_EXPORT void UpdateWorld();
		DESCENDANT_EXPORT void RenderWorld(Framework::IRenderer* renderer);
		DESCENDANT_EXPORT void LoadWorld(std::string worldName);
		DESCENDANT_EXPORT void SaveWorld();

		DESCENDANT_EXPORT inline Framework::World* GetCurrentWorld() { return _curretWorld; }

		template <class T> inline void SetWorldControllers(std::unordered_map<std::string, T*> playercontrollers)
		{
			if (_curretWorld)
			{
				_curretWorld->SetPlayerControllers(playercontrollers);
			}
		}

	private:
		Framework::ISoundManager*	_soundManager;
		Framework::World*			_curretWorld;
		std::string					_worldPath;
		std::string					_texturePath;
	};
}

#endif // WORLDMANAGER_H