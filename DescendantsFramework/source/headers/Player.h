#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

// include headers that implement a archive in simple text format
#include <Boost/archive/text_oarchive.hpp>
#include <Boost/archive/text_iarchive.hpp>

namespace GameObject
{
	class Player : public GameObject
	{
		friend class boost::serialization::access;

	private:
		template<class Archive>
		inline void serialize(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & boost::serialization::base_object<GameObject>(*this);
		}

	public:
		DESCENDANT_EXPORT Player(std::string texturePath, SDL_Rect* position, SDL_Rect* destination);
		DESCENDANT_EXPORT Player();
		DESCENDANT_EXPORT virtual ~Player();

		DESCENDANT_EXPORT virtual void Update(SDL_Event* e);
	};
}

#endif // PLAYER_H