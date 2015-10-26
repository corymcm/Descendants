#include "stdafx.h"
#include "GameObject.h"


BOOST_CLASS_TRACKING(Framework::GameObject, boost::serialization::track_always);

Framework::GameObject::GameObject(std::string textureName, Rect* source, Rect* destination)
	:_currentState(EGameObjectState::ALIVE)
{
	if (source != nullptr)
	{
		SourceRect =  Rect(*source);
	}

	if (destination != nullptr)
	{
		DestRect = Rect(*destination);
	}

	_textureName = textureName;
}

Framework::GameObject::~GameObject()
{

}

void Framework::GameObject::Update()
{

}

