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
		int _dest_x = 0;
		int _dest_y = 0;
		int _dest_w = 0;
		int _dest_h = 0;

		DESCENDANT_EXPORT SDL_Rect* GetDestination()
		{
			if (_dest_x == 0 && _dest_y == 0 && _dest_w == 0 && _dest_h == 0)
				return nullptr;
			return new SDL_Rect{ _dest_x, _dest_y, _dest_w, _dest_h };
		};

		template<class Archive>
		void save(Archive & ar, const unsigned int version) const
		{
			DESCENDANT_UNUSED(version);

			ar & boost::serialization::base_object<GameObject>(*this);
			ar & _dest_x;
			ar & _dest_y;
			ar & _dest_w;
			ar & _dest_h;
		}

		template<class Archive>
		void load(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & boost::serialization::base_object<GameObject>(*this);
			ar & _dest_x;
			ar & _dest_y;
			ar & _dest_w;
			ar & _dest_h;
		}

		BOOST_SERIALIZATION_SPLIT_MEMBER()

	public:
		DESCENDANT_EXPORT Pawn(std::string texturePath, SDL_Renderer* renderer, SDL_Rect* position, SDL_Rect* destination);
		DESCENDANT_EXPORT Pawn();

		DESCENDANT_EXPORT virtual ~Pawn();

		DESCENDANT_EXPORT virtual void Update(SDL_Event* e);
		DESCENDANT_EXPORT virtual void Render(SDL_Renderer* renderer);
	};
}

#endif // PAWN_H