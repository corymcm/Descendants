#pragma once

#ifndef SDL_PLAYERCONTROLLER_H
#define SDL_PLAYERCONTROLLER_H

#include <SDL.h>

#include "IPlayerController.h"
#include "GameObject.h"
#include <vector>

namespace Controllers
{
	class SDL_PlayerController : public Framework::IPlayerController
	{
	public:
		SDL_PlayerController();
		~SDL_PlayerController();

		virtual void UpdateController(GameObject::GameObject* object) override;
		virtual std::string GetName() override
		{
			return _name;
		}

		inline void AddEvents(void* event) override
		{
			SDL_Event* sdlEvent = static_cast<SDL_Event*>(event);
			_eventQueue.push_back(sdlEvent);
		}

	private:
		std::string _name;
		std::vector<SDL_Event*> _eventQueue;

	};
}

#endif // SDL_PLAYERCONTROLLER_H