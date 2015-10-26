#include "stdafx.h"
#include "WorldManager.h"
#include <fstream>

WorldManager::WorldManager::WorldManager(std::string resourcePath, Framework::ISoundManager* soundManager)
	: _curretWorld(NULL),
	_soundManager(NULL)
{
	_worldPath = resourcePath + "Worlds\\";
	_texturePath = resourcePath + "Textures\\";
	_soundManager = soundManager;
}

WorldManager::WorldManager::WorldManager(std::string resourcePath, Framework::ISoundManager* soundManager, Framework::World* world)
	: WorldManager::WorldManager(resourcePath, soundManager)
{
	_curretWorld = world;
	_curretWorld->SetTexturePath(_texturePath);
}

WorldManager::WorldManager::~WorldManager()
{
	delete _curretWorld;
	delete _soundManager;
}

void WorldManager::WorldManager::UpdateWorld()
{
	_curretWorld->Update(_soundManager);
}

void WorldManager::WorldManager::RenderWorld(Framework::IRenderer* renderer)
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
