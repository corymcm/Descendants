#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

namespace GameObject
{
	class GameObject
	{
	private:
		SDL_Texture* _texture;
		SDL_Rect* _position;

	public:
		GameObject(SDL_Texture* texture, int posx, int posy, int width, int height);
		GameObject(SDL_Texture* texture, SDL_Rect* position);
		virtual ~GameObject();

		virtual void Update();
		virtual void Render(SDL_Renderer* renderer);
	};
}

#endif // GAMEOBJECT_H