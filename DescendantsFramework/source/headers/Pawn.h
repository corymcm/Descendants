#pragma once

#ifndef PAWN_H
#define PAWN_H

#include "GameObject.h"

// Need to forward declare our class and serialization functions so boost can have access to our member variables.
namespace Framework
{
	class Pawn;
}

namespace boost
{
	namespace serialization
	{
		template<class Archive> void save_construct_data(Archive& ar, const Framework::Pawn* t, const unsigned int version);
		template<class Archive> void load_construct_data(Archive& ar, Framework::Pawn* t, const unsigned int version);
	}
}

namespace Framework
{
	class Pawn : public GameObject
	{
	public:
		DESCENDANT_EXPORT Pawn(std::string texturePath, Rect* source, Rect* destination);
		DESCENDANT_EXPORT virtual ~Pawn();

		DESCENDANT_EXPORT virtual void Update() override;

	private:
		friend class boost::serialization::access;
		template<class Archive> inline void serialize(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & boost::serialization::base_object<GameObject>(*this);
		}

		template<class Archive> friend void boost::serialization::save_construct_data(Archive& ar, const Pawn* t, const unsigned int version);
		template<class Archive> friend void boost::serialization::load_construct_data(Archive& ar, Pawn* t, const unsigned int version);
	};
}

template<class Archive> inline void boost::serialization::save_construct_data(Archive& ar, const Framework::Pawn* t, const unsigned int version)
{
	DESCENDANT_UNUSED(version);

	// save data required to construct instance
	std::string texture = t->GetTextureName();
	ar << t->DestRect;
	ar << t->SourceRect;
	ar << texture;
}

template<class Archive> inline void boost::serialization::load_construct_data(Archive& ar, Framework::Pawn* t, const unsigned int version)
{
	DESCENDANT_UNUSED(version);

	// retrieve data from archive required to construct new instance
	std::string textureName;
	Framework::Rect src;
	Framework::Rect dest;

	ar >> dest;
	ar >> src;
	ar >> textureName;

	// invoke in place constructor to initialize instance of Pawn
	::new(t)Framework::Pawn(textureName, &src, &dest);
}

#endif // PAWN_H