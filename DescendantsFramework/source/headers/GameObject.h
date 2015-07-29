#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <unordered_map> 

// include headers that implement a archive in simple text format
#include <Boost/archive/text_oarchive.hpp>
#include <Boost/archive/text_iarchive.hpp>
#include <boost/serialization/unordered_map.hpp>

namespace GameObject
{
	enum class EGameObjectState : unsigned int
	{
		Alive,
		Dead,
		Moving,
		Collided,
		USED,
		USING,
		FIRING
	};

	class Rect
	{
		friend class boost::serialization::access;

	public:
		int x;
		int y;
		int w;
		int h;

		bool IsEmpty()
		{
			return x == 0 && y == 0 && w == 0 && h == 0;
		}

	private:
		template<class Archive>
		inline void serialize(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & x;
			ar & y;
			ar & w;
			ar & h;
		}
	};

	class GameObject
	{
		friend class boost::serialization::access;

	private:
		std::string _textureName;

		template<class Archive>
		inline void serialize(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & _textureName;
			ar & _soundDictionary;

			ar & SourceRect;
			ar & DestRect;
		}

		std::unordered_map<EGameObjectState, std::string> _soundDictionary;

	public:
		Rect DestRect;
		Rect SourceRect;

		DESCENDANT_EXPORT GameObject(std::string textureName, SDL_Rect* source, SDL_Rect* destination);
		DESCENDANT_EXPORT GameObject();

		virtual DESCENDANT_EXPORT ~GameObject();

		inline std::string GetTextureName() const { return _textureName; }

		inline std::string GetSound(EGameObjectState eState)
		{
			auto search = _soundDictionary.find(eState);
			return search != _soundDictionary.end() ? search->second : nullptr;
		}

		virtual void DESCENDANT_EXPORT Update(SDL_Event* e);
	};
}

#endif // GAMEOBJECT_H