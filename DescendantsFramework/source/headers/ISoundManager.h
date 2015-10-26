#pragma once

#ifndef ISOUNDMANAGER_H
#define ISOUNDMANAGER_H

namespace Framework
{
	class ISoundManager
	{
	public:
		virtual ~ISoundManager() {};

		virtual void		PlayEffect(std::string sound)	= 0;
		virtual void		PlayMusic(std::string sound)	= 0;
		virtual void		PauseMusic()					= 0;
		virtual void		StopMusic()						= 0;
		virtual std::string GetCurrentMusic()				= 0;
	};
}

#endif // ISOUNDMANAGER_H