#include "stdafx.h"
#include "SDL_PlayerController.h"


Controllers::SDL_PlayerController::SDL_PlayerController()
{
	_eventQueue = std::vector<SDL_Event*>();
}

Controllers::SDL_PlayerController::~SDL_PlayerController()
{

}

void Controllers::SDL_PlayerController::UpdateController(Framework::GameObject* object)
{
	for (const auto &e : _eventQueue)
	{
		if (e->type == SDL_KEYDOWN)
		{
			switch (e->key.keysym.sym)
			{
			case SDLK_w:
				object->DestRect.y -= 1;
				break;
			case SDLK_s:
				object->DestRect.y += 1;
				break;
			case SDLK_a:
				object->DestRect.x -= 1;
				break;
			case SDLK_d:
				object->DestRect.x += 1;
				break;
			default:
				break;
			}
			return;
		}
	}
}
