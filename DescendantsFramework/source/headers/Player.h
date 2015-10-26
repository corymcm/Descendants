#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "IPlayerController.h"

// Need to forward declare our class and serialization functions so boost can have access to our member variables.
namespace Framework
{
	class Player;
}

namespace boost
{
	namespace serialization
	{
		template<class Archive> void save_construct_data(Archive& ar, const Framework::Player* t, const unsigned int version);
		template<class Archive> void load_construct_data(Archive& ar, Framework::Player* t, const unsigned int version);
	}
}

namespace Framework
{
	class Player : public GameObject
	{
	public:
		DESCENDANT_EXPORT Player(std::string texturePath, Rect* source, Rect* destination, std::string controllerName, int maxLives);
		DESCENDANT_EXPORT virtual ~Player();

		std::string ControllerName;

		DESCENDANT_EXPORT virtual void Update() override;

		inline void SetPlayerController(Framework::IPlayerController* pc)
		{
			_playerController = pc;
		}

		inline int GetLives() const { return _lives; }

	private:
		Framework::IPlayerController*	_playerController;
		int								_lives;
		
		friend class boost::serialization::access;
		template<class Archive> inline void serialize(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & boost::serialization::base_object<GameObject>(*this);
			ar & ControllerName;
		}

		template<class Archive> friend void boost::serialization::save_construct_data(Archive& ar, const Player* t, const unsigned int version);
		template<class Archive> friend void boost::serialization::load_construct_data(Archive& ar, Player* t, const unsigned int version);
	};
}

template<class Archive> inline void boost::serialization::save_construct_data(Archive& ar, const Framework::Player* t, const unsigned int version)
{
	DESCENDANT_UNUSED(version);

	// save data required to construct instance
	std::string texture = t->GetTextureName();
	ar << t->DestRect;
	ar << t->SourceRect;
	ar << texture;
	ar << t->ControllerName;
	ar << t->_lives;
}

template<class Archive> inline void boost::serialization::load_construct_data(Archive& ar, Framework::Player* t, const unsigned int version)
{
	DESCENDANT_UNUSED(version);

	// retrieve data from archive required to construct new instance
	std::string controllerName;
	std::string textureName;
	Framework::Rect src;
	Framework::Rect dest;
	int lives;

	ar >> dest;
	ar >> src;
	ar >> textureName;
	ar >> controllerName;
	ar >> lives;

	// invoke in place constructor to initialize instance of Player
	::new(t)Framework::Player(textureName, &src, &dest, controllerName, lives);
}

#endif // PLAYER_H