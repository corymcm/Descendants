#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "IPlayerController.h"

// include headers that implement a archive in simple text format
#include <Boost/archive/text_oarchive.hpp>
#include <Boost/archive/text_iarchive.hpp>

namespace GameObject
{
	class Player : public GameObject
	{
		friend class boost::serialization::access;

	private:
		Framework::IPlayerController* _playerController;

		template<class Archive>
		inline void serialize(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & boost::serialization::base_object<GameObject>(*this);
			ar & ControllerName;
		}

	public:
		DESCENDANT_EXPORT Player(std::string texturePath, Rect* position, Rect* destination, std::string controllerName);
		DESCENDANT_EXPORT Player();
		DESCENDANT_EXPORT virtual ~Player();

		DESCENDANT_EXPORT virtual void Update();

		std::string ControllerName;

		inline void SetPlayerController(Framework::IPlayerController* pc)
		{
			_playerController = pc;
		}
	};
}

#endif // PLAYER_H