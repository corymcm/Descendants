#pragma once

#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "GameObject.h"
#include "IRenderer.h"
#include "ISoundManager.h"
#include "IPlayerController.h"

// include headers that implement a archive in simple text format
#include <Boost/archive/text_oarchive.hpp>
#include <Boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

namespace World
{
	class World
	{
		friend class boost::serialization::access;
	private:
		std::vector<GameObject::GameObject*> _objects;
		std::string _name;
		std::string _texturePath;
		std::string _backgroundMusic;

		World();
		inline void SetName(std::string name) { _name = name; }
		
		template<class Archive>
		inline void serialize(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & _name;
			ar & _backgroundMusic;
			ar & _objects;
		}

	public:
		DESCENDANT_EXPORT World(std::string fileName);
		DESCENDANT_EXPORT virtual ~World();

		inline std::string GetName() { return _name; }
		inline void SetTexturePath(std::string path) { _texturePath = path; }
		inline void SetBackgroundMusic(std::string sound) { _backgroundMusic = sound; }

		DESCENDANT_EXPORT void Update(Framework::ISoundManager* soundManager);
		DESCENDANT_EXPORT void Render(Framework::IRenderer* renderer);
		DESCENDANT_EXPORT void AddObject(GameObject::GameObject* object);
		DESCENDANT_EXPORT void RemoveObject(GameObject::GameObject* object);

		template <class T>
		void SetPlayerControllers(std::unordered_map<std::string, T*> playercontrollers)
		{
			for (auto object : _objects)
			{
				GameObject::Player* player = dynamic_cast<GameObject::Player*>(object);
				if (player == nullptr)
					continue;
				auto search = playercontrollers.find(player->ControllerName);
				if (search != playercontrollers.end())
				{
					player->SetPlayerController(search->second);
				}
			}
		}

	};
}

#endif // WORLD_H