#pragma once

#ifndef SDL_PLAYERCONTROLLER_H
#define SDL_PLAYERCONTROLLER_H

#include <SDL.h>

#include "IPlayerController.h"
#include <vector>

namespace Controllers
{
	class SDL_PlayerController : public Framework::IPlayerController
	{
	public:
		SDL_PlayerController();
		~SDL_PlayerController();

		virtual void UpdateController(Framework::GameObject* object) override;
		virtual std::string GetName() override
		{
			return _name;
		}

		inline void AddEvent(SDL_Event* event)
		{
			_eventQueue.push_back(event);
		}

		inline void ClearEvents()
		{
			_eventQueue.clear();
		}

	private:
		std::string _name;
		std::vector<SDL_Event*> _eventQueue;

	};
}

#endif // SDL_PLAYERCONTROLLER_H