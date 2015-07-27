#include "stdafx.h"
#include "SDL_SoundManager.h"

SoundManager::SDL_SoundManager::SDL_SoundManager(std::string path)
{
	_basePath = path;

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		LogError("Could not Initilize SDL_Mixer: ");
	}
}

SoundManager::SDL_SoundManager::~SDL_SoundManager()
{
	for (auto it = _effectDictionary.begin(); it != _effectDictionary.end();)
	{
		Mix_FreeChunk(it->second);
		it = _effectDictionary.erase(it);
	}

	for (auto it = _musicDictionary.begin(); it != _musicDictionary.end();)
	{
		Mix_FreeMusic(it->second);
		it = _musicDictionary.erase(it);
	}
}

void SoundManager::SDL_SoundManager::PlayEffect(std::string sound)
{
	Mix_Chunk* effect = QueryEffectDictionary(sound);
	if (effect == nullptr)
	{
		LogError("Could not Find Sound Effect: ");
		return;
	}
	if (Mix_PlayChannel(-1, effect, 0) == -1)
	{
		LogError("Error Playing Sound Effect: ");
		return;
	}
}

Mix_Chunk* SoundManager::SDL_SoundManager::QueryEffectDictionary(std::string name)
{
	auto search = _effectDictionary.find(name);
	return search != _effectDictionary.end() ? search->second : LoadEffect(_basePath + name);
}

Mix_Chunk* SoundManager::SDL_SoundManager::LoadEffect(std::string name)
{
	Mix_Chunk *chunk = Mix_LoadWAV(name.c_str());
	if (chunk == NULL)
	{
		LogError("SDL_Mixer Error: ");
		return nullptr;
	}

	_effectDictionary[name] = chunk;
	return chunk;
}

void SoundManager::SDL_SoundManager::PlayMusic(std::string sound)
{
	Mix_Music* music = QueryMusicDictionary(sound);
	if (music == nullptr)
	{
		LogError("Could not Find Sound: ");
		return;
	}

	if (Mix_PlayingMusic() == 1)
	{
		StopMusic();
	}

	if (Mix_PlayMusic(music, -1) == -1)
	{
		LogError("Error Playing Music: ");
		return;
	}

	_currentMusic = sound;
}

void SoundManager::SDL_SoundManager::PauseMusic()
{
	if (Mix_PausedMusic() == 1)
	{
		return;
	}

	Mix_PauseMusic();
}

void SoundManager::SDL_SoundManager::StopMusic()
{
	if (Mix_PlayingMusic() == 0)
	{
		return;
	}

	Mix_HaltMusic();
	_currentMusic = "";
}

Mix_Music* SoundManager::SDL_SoundManager::QueryMusicDictionary(std::string name)
{
	auto search = _musicDictionary.find(name);
	return search != _musicDictionary.end() ? search->second : LoadMusic(_basePath + name);
}

Mix_Music* SoundManager::SDL_SoundManager::LoadMusic(std::string name)
{
	Mix_Music *mus = Mix_LoadMUS(name.c_str());
	if (mus == NULL)
	{
		LogError("SDL_Mixer Error: ");
		return nullptr;
	}

	_musicDictionary[name] = mus;
	return mus;
}