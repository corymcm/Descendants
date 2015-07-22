#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "GameObject.h"

namespace Framework
{
	class Renderer
	{
	public:
		virtual ~Renderer() {};
		virtual void Render(GameObject::GameObject* obj) = 0;
		virtual void RenderPresent() = 0;
		virtual void ClearRenderer() = 0;
		virtual void* GetRendererPtr() = 0;
	};
}

#endif // RENDERER_H