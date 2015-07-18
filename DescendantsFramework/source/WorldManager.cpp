#include "stdafx.h"
#include "WorldManager.h"
#include <fstream>

WorldManager::WorldManager::WorldManager(std::string resourcePath)
	: _curretWorld(NULL)
{
	_worldResourceFolder = resourcePath;
}

WorldManager::WorldManager::WorldManager(std::string resourcePath, World::World* world)
	: WorldManager::WorldManager(resourcePath)
{
	_curretWorld = world;
}

WorldManager::WorldManager::~WorldManager()
{
	delete _curretWorld;
}

void WorldManager::WorldManager::UpdateWorld(SDL_Event* e)
{
	_curretWorld->Update(e);
}

void WorldManager::WorldManager::RenderWorld(SDL_Renderer* renderer)
{
	SDL_RenderClear(renderer);
	_curretWorld->Render(renderer);
}

void WorldManager::WorldManager::LoadWorld(std::string worldName)
{
	std::ifstream ifs(_worldResourceFolder + worldName);
	{
		boost::archive::text_iarchive ia(ifs);
		ia & _curretWorld;
	}
}

void WorldManager::WorldManager::SaveWorld()
{
	std::ofstream ofs(_worldResourceFolder + _curretWorld->GetName());
	{
		boost::archive::text_oarchive oa(ofs);
		oa & _curretWorld;
	}
}
