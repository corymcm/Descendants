#pragma once

#ifndef SDL_TEXTUREMANAGER
#define SDL_TEXTUREMANAGER

#include <SDL.h>
#include <unordered_map> 

namespace TextureManager
{
	class SDL_TextureManager
	{
	private:
		std::unordered_map<std::string, SDL_Texture*> _textureDictionary;
		std::string _basepath;

		SDL_Surface* LoadBitmap(std::string path);
		SDL_Texture* LoadTexture(std::string name, SDL_Renderer* renderer);

	public:
		SDL_TextureManager(std::string path);
		~SDL_TextureManager();

		SDL_Texture* GetTexture(std::string name, SDL_Renderer* renderer);
	};
}

#endif // SDL_TEXTUREMANAGER