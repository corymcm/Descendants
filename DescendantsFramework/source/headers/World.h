#pragma once

#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Player.h"
#include "IRenderer.h"
#include "ISoundManager.h"
#include "ISpawner.h"

#include <boost/serialization/vector.hpp>

// Need to forward declare our class and serialization functions so boost can have access to our member variables.
namespace Framework
{
	class World;
}

namespace boost
{
	namespace serialization
	{
		template<class Archive> void save_construct_data(Archive& ar, const Framework::World* t, const unsigned int version);
		template<class Archive> void load_construct_data(Archive& ar, Framework::World* t, const unsigned int version);
	}
}

namespace Framework
{
	class World
	{
	public:
		DESCENDANT_EXPORT World(std::string fileName);
		DESCENDANT_EXPORT virtual ~World();

		DESCENDANT_EXPORT void Update(Framework::ISoundManager*		soundManager);
		DESCENDANT_EXPORT void Render(Framework::IRenderer*			renderer);
		DESCENDANT_EXPORT void AddObject(Framework::GameObject*		object);
		DESCENDANT_EXPORT void RemoveObject(Framework::GameObject*	object);
		DESCENDANT_EXPORT void AddSpawner(Framework::ISpawner*		spawner);
		DESCENDANT_EXPORT void RemoveSpawner(Framework::ISpawner*	spawner);

		inline std::string GetName() { return _name; }
		inline void SetTexturePath(std::string path) { _texturePath = path; }
		inline void SetBackgroundMusic(std::string sound) { _backgroundMusic = sound; }

		template <class T> void SetPlayerControllers(std::unordered_map<std::string, T*> playercontrollers)
		{
			// TODO add playerControllers to class and keep list internally, this way we can move this block to the update function.
			if (_players.empty())
			{
				for (auto spawner : _spawners)
				{
					auto playerSpawner = dynamic_cast<PlayerSpawner*>(spawner);
					if (playerSpawner != NULL)
					{
						if (!playerSpawner->IsActive())
							playerSpawner->Activate();
						_players.push_back(static_cast<Framework::Player*>(playerSpawner->Spawn()));
						break;
					}
				}
			}

			for (auto player : _players)
			{
				auto search = playercontrollers.find(player->ControllerName);
				if (search != playercontrollers.end())
				{
					player->SetPlayerController(search->second);
				}
			}
		}
		
	private:
		std::vector<Framework::GameObject*>		_objects;
		std::vector<Framework::ISpawner*>		_spawners;
		std::vector<Framework::Player*>			_players;
		std::string								_name;
		std::string								_texturePath;
		std::string								_backgroundMusic;
		const int								_maxLives;

		inline void SetName(std::string name) { _name = name; }

		friend class boost::serialization::access;
		template<class Archive> inline void serialize(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & _backgroundMusic;
			ar & _objects;
			ar & _spawners;
		}

		template<class Archive> friend void boost::serialization::save_construct_data(Archive& ar, const World* t, const unsigned int version);
		template<class Archive> friend void boost::serialization::load_construct_data(Archive& ar, World* t, const unsigned int version);
	};
}

template<class Archive> inline void boost::serialization::save_construct_data(Archive& ar, const Framework::World* t, const unsigned int version)
{
	DESCENDANT_UNUSED(version);

	ar << t->_name;
}

template<class Archive> inline void boost::serialization::load_construct_data(Archive& ar, Framework::World* t, const unsigned int version)
{
	DESCENDANT_UNUSED(version);

	// retrieve data from archive required to construct new instance
	std::string fileName;
	ar >> fileName;

	// invoke in place constructor to initialize instance of World
	::new(t)Framework::World(fileName);
}

#endif // WORLD_H