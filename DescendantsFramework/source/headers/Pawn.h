#pragma once

#ifndef PAWN_H
#define PAWN_H

#include "GameObject.h"

// include headers that implement a archive in simple text format
#include <Boost/archive/text_oarchive.hpp>
#include <Boost/archive/text_iarchive.hpp>

namespace GameObject
{
	class Pawn : public GameObject
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
		DESCENDANT_EXPORT Pawn(std::string texturePath, Rect* position, Rect* destination);
		DESCENDANT_EXPORT Pawn();

		DESCENDANT_EXPORT virtual ~Pawn();

		DESCENDANT_EXPORT virtual void Update(SDL_Event* e);
	};
}

#endif // PAWN_H