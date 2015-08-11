#pragma once

#ifndef IPLAYERCONTROL_H
#define IPLAYERCONTROL_H

#include "GameObject.h"

namespace Framework
{
	class IPlayerController
	{
	public:
		virtual ~IPlayerController() {};
		virtual void UpdateController(GameObject::GameObject* object) = 0;
		virtual std::string GetName() = 0;
	};
}


#endif // IPLAYERCONTROL_H