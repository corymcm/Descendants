#pragma once

#ifndef PLAYERSPAWNER_H
#define PLAYERSPAWNER_H

#include "ISpawner.h"

// Need to forward declare our class and serialization functions so boost can have access to our member variables.
namespace Framework
{
	class PlayerSpawner;
}

namespace boost 
{
	namespace serialization 
	{
		template<class Archive> void save_construct_data(Archive& ar, const Framework::PlayerSpawner* t, const unsigned int version);
		template<class Archive> void load_construct_data(Archive& ar, Framework::PlayerSpawner* t, const unsigned int version);
	}
}

namespace Framework
{
	class PlayerSpawner : public ISpawner
	{
	public:
		DESCENDANT_EXPORT PlayerSpawner(const std::string, const std::string, Rect*, Rect*, const int maxLives);

		GameObject*				Spawn()							override;
		void					ResetObject(GameObject* object) override;

		inline void Activate() override
		{
			_isActive = true;
		}

		inline void Deactivate() override
		{
			_isActive = false;
		}

		inline bool IsActive() const override
		{
			return _isActive;
		}

	private:
		const std::string	_playerController;
		const std::string	_textureName;
		Rect*				_src;
		Rect*				_dest;
		bool				_isActive;
		const int			_maxLives;

		friend class boost::serialization::access;
		template<class Archive> friend void boost::serialization::save_construct_data(Archive& ar, const PlayerSpawner* t, const unsigned int version);
		template<class Archive> friend void boost::serialization::load_construct_data(Archive& ar, PlayerSpawner* t, const unsigned int version);

		template<class Archive> inline void serialize(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);
			ar & boost::serialization::base_object<ISpawner>(*this);
			ar & _isActive;
		}
	};
}

template<class Archive> inline void boost::serialization::save_construct_data(Archive& ar, const Framework::PlayerSpawner* t, const unsigned int version)
{
	DESCENDANT_UNUSED(version);

	// save data required to construct instance
	ar << t->_dest;
	ar << t->_src;
	ar << t->_textureName;
	ar << t->_playerController;
	ar << t->_maxLives;
}

template<class Archive> inline void boost::serialization::load_construct_data(Archive& ar, Framework::PlayerSpawner* t, const unsigned int version)
{
	DESCENDANT_UNUSED(version);

	// retrieve data from archive required to construct new instance
	std::string playerController;
	std::string textureName;
	Framework::Rect* src;
	Framework::Rect* dest;
	int lives;

	ar >> dest;
	ar >> src;
	ar >> textureName;
	ar >> playerController;
	ar >> lives;

	// invoke in place constructor to initialize instance of PlayerSpawner
	::new(t)Framework::PlayerSpawner(textureName, playerController, src, dest, lives);
}

#endif // PLAYERSPAWNER_H