#include "stdafx.h"
#include "PlayerSpawner.h"
#include "Player.h"

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(Framework::PlayerSpawner, "PlayerSpawner");

Framework::PlayerSpawner::PlayerSpawner(const std::string textureName, const std::string playerContoller, Framework::Rect* src, Framework::Rect* dest, const int maxLives)
	: _textureName(textureName),
	_playerController(playerContoller),
	_isActive(false),
	_src(src),
	_dest(dest),
	_maxLives(maxLives)
{

}

Framework::GameObject* Framework::PlayerSpawner::Spawn()
{
	if (!_isActive)
		return nullptr;

	Framework::GameObject* retObjet = new Framework::Player(_textureName, _src, _dest, _playerController, _maxLives);

	return retObjet;
}

void Framework::PlayerSpawner::ResetObject(Framework::GameObject* object)
{
	object->Reset();
	object->DestRect = *_dest;
	object->SourceRect = *_src;
}

