#pragma once

#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "GameObject.h"

// include headers that implement a archive in simple text format
#include <Boost/archive/text_oarchive.hpp>
#include <Boost/archive/text_iarchive.hpp>

namespace World
{
	class DESCENDANT_EXPORT World
	{
		friend class boost::serialization::access;
	private:
		std::vector<GameObject::GameObject*>* _objects;
		std::string* _name;

		World();
		inline void SetName(std::string* name) { _name = name; }
		void LoadWorld();

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & _name;
			for (auto object : _objects)
			{
				ar & object;
			}
		}


	public:
		World(std::string fileName);
		~World();

		inline std::string* GetName() { return _name; }

		void Update(SDL_Event* e);
	};
}

#endif // WORLD_H