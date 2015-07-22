#pragma once

#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "GameObject.h"
#include "Renderer.h"

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

		World();
		inline void SetName(std::string name) { _name = name; }
		
		template<class Archive>
		inline void serialize(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & _name;
			ar & _objects;
		}

	public:
		DESCENDANT_EXPORT World(std::string fileName);
		DESCENDANT_EXPORT virtual ~World();

		DESCENDANT_EXPORT inline std::string GetName() { return _name; }
		DESCENDANT_EXPORT inline void SetTexturePath(std::string path) { _texturePath = path; }

		DESCENDANT_EXPORT void Update(SDL_Event* e);
		DESCENDANT_EXPORT void Render(Framework::Renderer* renderer);
		DESCENDANT_EXPORT void AddObject(GameObject::GameObject* object);
		DESCENDANT_EXPORT void RemoveObject(GameObject::GameObject* object);
	};
}

#endif // WORLD_H