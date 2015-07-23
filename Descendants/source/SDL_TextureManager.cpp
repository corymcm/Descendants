#include "stdafx.h"
#include "SDL_TextureManager.h"

TextureManager::SDL_TextureManager::SDL_TextureManager(std::string path)
{
	_basepath = path;
}

TextureManager::SDL_TextureManager::~SDL_TextureManager()
{
	for (auto it = _textureDictionary.begin(); it != _textureDictionary.end();)
	{
		SDL_DestroyTexture(it->second);
		it = _textureDictionary.erase(it);
	}
}

SDL_Texture* TextureManager::SDL_TextureManager::GetTexture(std::string name, SDL_Renderer* renderer)
{
	auto search = _textureDictionary.find(name);
	return search != _textureDictionary.end() ? search->second : LoadTexture(name, renderer);
}

SDL_Surface* TextureManager::SDL_TextureManager::LoadBitmap(std::string path)
{
	SDL_Surface* bmp = SDL_LoadBMP(path.c_str());
	if (bmp == nullptr)
	{
		LogError("SDL_LoadBMP Error: ");
		return nullptr;
	}
	return bmp;
}

SDL_Texture* TextureManager::SDL_TextureManager::LoadTexture(std::string name, SDL_Renderer* renderer)
{
	SDL_Surface* bmp = LoadBitmap(_basepath + name);

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr)
	{
		LogError("SDL_CreateTextureFromSurface Error: ");
		return nullptr;
	}

	_textureDictionary[name] = tex;
	return tex;
}
