#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <unordered_map> 

// include headers that implement a archive in simple text format
#include <Boost/archive/text_oarchive.hpp>
#include <Boost/archive/text_iarchive.hpp>

// Need to forward declare our class and serialization functions so boost can have access to our member variables.
namespace Framework
{
	class GameObject;
}

namespace boost
{
	namespace serialization
	{
		template<class Archive> void save_construct_data(Archive& ar, const Framework::GameObject* t, const unsigned int version);
		template<class Archive> void load_construct_data(Archive& ar, Framework::GameObject* t, const unsigned int version);
	}
}

#include <boost/serialization/unordered_map.hpp>


namespace Framework
{
	enum class EGameObjectState : unsigned int
	{
		ALIVE,
		DEAD,
		MOVING,
		COLLIED,
		USED,
		USING,
		FIRING
	};

	class Rect
	{
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
		friend class boost::serialization::access;
		template<class Archive> inline void serialize(Archive & ar, const unsigned int version)
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
	public:
		DESCENDANT_EXPORT GameObject(std::string textureName, Rect* source, Rect* destination);

		virtual DESCENDANT_EXPORT ~GameObject();

		Rect DestRect;
		Rect SourceRect;
		EGameObjectState _currentState;

		virtual void		DESCENDANT_EXPORT Update();
		virtual inline void DESCENDANT_EXPORT Reset() { _currentState = EGameObjectState::ALIVE; }

		inline std::string GetTextureName() const { return _textureName; }

		inline std::string GetSound(EGameObjectState eState)
		{
			auto search = _soundDictionary.find(eState);
			return search != _soundDictionary.end() ? search->second : nullptr;
		}

		inline EGameObjectState GetCurrentState()
		{
			return _currentState;
		}

	private:
		std::string _textureName;
		std::unordered_map<EGameObjectState, std::string> _soundDictionary;

		friend class boost::serialization::access;
		template<class Archive> inline void serialize(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & _soundDictionary;
		}

		template<class Archive> friend void boost::serialization::save_construct_data(Archive& ar, const GameObject* t, const unsigned int version);
		template<class Archive> friend void boost::serialization::load_construct_data(Archive& ar, GameObject* t, const unsigned int version);
	};
}

template<class Archive> inline void boost::serialization::save_construct_data(Archive& ar, const Framework::GameObject* t, const unsigned int version)
{
	DESCENDANT_UNUSED(version);

	// save data required to construct instance
	ar << t->DestRect;
	ar << t->SourceRect;
	ar << t->_textureName;
}

template<class Archive> inline void boost::serialization::load_construct_data(Archive& ar, Framework::GameObject* t, const unsigned int version)
{
	DESCENDANT_UNUSED(version);

	// retrieve data from archive required to construct new instance
	std::string textureName;
	Framework::Rect src;
	Framework::Rect dest;

	ar >> dest;
	ar >> src;
	ar >> textureName;

	// invoke in place constructor to initialize instance of GameObject
	::new(t)Framework::GameObject(textureName, &src, &dest);
}

#endif // GAMEOBJECT_H