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
			ar & src_x;
			ar & src_y;
			ar & src_w;
			ar & src_h;

			ar & dest_x;
			ar & dest_y;
			ar & dest_w;
			ar & dest_h;
		}

	protected:
		int src_x = 0;
		int src_y = 0;
		int src_w = 0;
		int src_h = 0;

		int dest_x = 0;
		int dest_y = 0;
		int dest_w = 0;
		int dest_h = 0;

		std::unordered_map<EGameObjectState, std::string> _soundDictionary;

	public:
		DESCENDANT_EXPORT GameObject(std::string textureName, SDL_Rect* source, SDL_Rect* destination);
		DESCENDANT_EXPORT GameObject();

		virtual DESCENDANT_EXPORT ~GameObject();

		inline std::string GetTextureName() const { return _textureName; }

		inline SDL_Rect* GetDestination()
		{
			if (dest_x == 0 && dest_y == 0 && dest_w == 0 && dest_h == 0)
				return nullptr;
			return new SDL_Rect{ dest_x, dest_y, dest_w, dest_h };
		};

		inline SDL_Rect* GetSource()
		{
			if (src_x == 0 && src_y == 0 && src_w == 0 && src_h == 0)
				return nullptr;
			return new SDL_Rect{ src_x, src_y, src_w, src_h };
		};

		inline std::string GetSound(EGameObjectState eState)
		{
			auto search = _soundDictionary.find(eState);
			return search != _soundDictionary.end() ? search->second : nullptr;
		}

		virtual void DESCENDANT_EXPORT Update(SDL_Event* e);
	};
}

#endif // GAMEOBJECT_H