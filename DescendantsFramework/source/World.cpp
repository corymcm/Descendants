#include "stdafx.h"
#include "World.h"
#include "Player.h"

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(World::World, "World");

World::World::World()
{

}

World::World::World(std::string fileName)
	:World()
{
	SetName(fileName);
}

World::World::~World()
{
	while (!_objects.empty()) delete _objects.back(), _objects.pop_back();
}

void World::World::Update(Framework::ISoundManager* soundManager)
{
	if (soundManager->GetCurrentMusic() != _backgroundMusic)
	{
		soundManager->PlayMusic(_backgroundMusic);
	}

	for (auto object : _objects)
	{
		object->Update();
	}
}

void World::World::Render(Framework::IRenderer* renderer)
{
	for (auto object : _objects)
	{
		renderer->Render(object, _texturePath);
	}
}

void World::World::AddObject(GameObject::GameObject* object)
{
	_objects.push_back(object);
}

void World::World::RemoveObject(GameObject::GameObject* object)
{
	DESCENDANT_UNUSED(object);
}

void World::World::SetPlayerControllers(std::unordered_map<std::string, Framework::IPlayerController*> playercontrollers)
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

