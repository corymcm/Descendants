#include "stdafx.h"
#include "World.h"
#include "Pawn.h"
#include "Player.h"
#include "PlayerSpawner.h"

#include <algorithm>

Framework::World::World(std::string fileName)
	:_maxLives(5)
{
	SetName(fileName);
}

Framework::World::~World()
{
	while (!_objects.empty()) delete _objects.back(), _objects.pop_back();

	while (!_spawners.empty()) delete _spawners.back(), _spawners.pop_back();

	while (!_players.empty()) delete _players.back(), _players.pop_back();
}

void Framework::World::Update(Framework::ISoundManager* soundManager)
{
	if (soundManager->GetCurrentMusic() != _backgroundMusic)
	{
		soundManager->PlayMusic(_backgroundMusic);
	}

	for (auto object : _objects)
	{
		object->Update();
	}

	for (auto player : _players)
	{
		player->Update();
		if (player->GetCurrentState() == EGameObjectState::DEAD && player->GetLives() > 0)
		{
			for (auto spawner : _spawners)
			{
				if (spawner->IsActive())
				{
					spawner->ResetObject(player);
					break;
				}
			}
		}
	}
}

void Framework::World::Render(Framework::IRenderer* renderer)
{
	for (auto object : _objects)
	{
		renderer->Render(object, _texturePath);
	}

	for (auto player : _players)
	{
		renderer->Render(player, _texturePath);
	}
}

void Framework::World::AddObject(Framework::GameObject* object)
{
	_objects.push_back(object);
}

void Framework::World::RemoveObject(Framework::GameObject* object)
{
	_objects.erase(std::remove(_objects.begin(), _objects.end(), object));
}

void Framework::World::AddSpawner(Framework::ISpawner* spawner)
{
	_spawners.push_back(spawner);
}

void Framework::World::RemoveSpawner(Framework::ISpawner* spawner)
{
	_spawners.erase(std::remove(_spawners.begin(), _spawners.end(), spawner));
}

