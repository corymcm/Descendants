#pragma once

#ifndef RENDERER_H
#define RENDERER_H

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

#endif // RENDERER_H