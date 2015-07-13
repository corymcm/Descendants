#include "stdafx.h"
#include "World.h"

World::World::World()
	:_name(nullptr),
	_objects(nullptr)
{

}
void World::World::LoadWorld()
{

}

World::World::World(std::string fileName)
	:World()
{
	SetName(&fileName);
}

World::World::~World()
{
	delete _name;
	while (!_objects->empty()) delete _objects->back(), _objects->pop_back();
	delete _objects;
}

void World::World::Update(SDL_Event* e)
{
	DESCENDANT_UNUSED(e);
}