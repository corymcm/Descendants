#pragma once

#ifndef IRENDERER_H
#define IRENDERER_H

#include "GameObject.h"

namespace Framework
{
	class IRenderer
	{
	public:
		virtual ~IRenderer() {};
		virtual void Render(GameObject::GameObject* obj, std::string texturePath) = 0;
		virtual void RenderPresent() = 0;
		virtual void ClearRenderer() = 0;
	};
}

#endif // IRENDERER_H