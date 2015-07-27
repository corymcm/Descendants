#pragma once

#ifndef SDL_SOUNDMANAGER_H
#define SDL_SOUNDMANAGER_H

#include "ISoundManager.h"
#include "SDL_mixer.h"
#include <unordered_map> 
#include <SDL.h>

namespace SoundManager
{
	class SDL_SoundManager : public Framework::ISoundManager
	{
	public:
		SDL_SoundManager(std::string path);
		~SDL_SoundManager();

		void PlayEffect(std::string sound) override;
		void PlayMusic(std::string sound) override;
		void PauseMusic() override;
		void StopMusic() override;

		std::string GetCurrentMusic() override 
		{
			return _currentMusic;
		}

	private:
		std::string _basePath;
		std::string _currentMusic;
		
		std::unordered_map<std::string, Mix_Chunk*> _effectDictionary;
		std::unordered_map<std::string, Mix_Music*> _musicDictionary;

		Mix_Chunk* QueryEffectDictionary(std::string name);
		Mix_Chunk* LoadEffect(std::string name);

		Mix_Music* QueryMusicDictionary(std::string name);
		Mix_Music* LoadMusic(std::string name);
	};
}

#endif // SDL_SOUNDMANAGER_H