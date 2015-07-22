#include "stdafx.h"
#include "WorldManager.h"
#include <fstream>

WorldManager::WorldManager::WorldManager(std::string resourcePath)
	: _curretWorld(NULL)
{
	_worldPath = resourcePath + "Worlds\\";
	_texturePath = resourcePath + "Textures\\";
}

WorldManager::WorldManager::WorldManager(std::string resourcePath, World::World* world)
	: WorldManager::WorldManager(resourcePath)
{
	_curretWorld = world;
	_curretWorld->SetTexturePath(_texturePath);
}

WorldManager::WorldManager::~WorldManager()
{
	delete _curretWorld;
}

void WorldManager::WorldManager::UpdateWorld(SDL_Event* e)
{
	_curretWorld->Update(e);
}

void WorldManager::WorldManager::RenderWorld(Framework::Renderer* renderer)
{
	renderer->ClearRenderer();
	_curretWorld->Render(renderer);
}

void WorldManager::WorldManager::LoadWorld(std::string worldName)
{
	std::ifstream ifs(_worldPath + worldName);
	{
		boost::archive::text_iarchive ia(ifs);
		ia & _curretWorld;
	}
	_curretWorld->SetTexturePath(_texturePath);
}

void WorldManager::WorldManager::SaveWorld()
{
	std::ofstream ofs(_worldPath + _curretWorld->GetName());
	{
		boost::archive::text_oarchive oa(ofs);
		oa & _curretWorld;
	}
}
