#include "stdafx.h"

#include "main.h"
#include "WindowManager.h"
#include "GameObject.h"
#include "Pawn.h"
#include "Player.h"
#include <fstream>

// TODO : Wrap this in a game object
// global objects are ugly, same with the g_ prefix...
WindowManger::WindowManger* g_windowManager;

#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(GameObject::Player, "Player");
BOOST_CLASS_EXPORT_GUID(GameObject::Pawn, "Pawn");

///-------------------------------------------------
/// Initialize main gameobject and windowmangers.
///-------------------------------------------------
bool InitializeGameObject()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		LogError("SDL_Init Error: ");
		return false;
	}

	std::string TexturePath = SDL_GetBasePath();
	TexturePath.append("..\\..\\..\\Data\\Textures\\");

	g_windowManager = new WindowManger::WindowManger("You son of a bitch!", 100, 100, 640, 480);
	SDL_Rect* dilion_position = new SDL_Rect{ 200, 200, 64, 64 };
	SDL_Rect* dutch_position = new SDL_Rect{ 50, 200, 64, 64 };

	GameObject::GameObject* Background = new GameObject::GameObject(std::string(TexturePath).append("background.bmp"), g_windowManager->GetRenderer(), NULL, NULL);
	GameObject::GameObject* dilionPawn = new GameObject::Pawn(std::string(TexturePath).append("dilion.bmp"), g_windowManager->GetRenderer(), NULL, dilion_position);
	GameObject::GameObject* dutchPlayer = new GameObject::Player(std::string(TexturePath).append("dutch.bmp"), g_windowManager->GetRenderer(), NULL, dutch_position);

	//Serialization test
	//std::ofstream ofs("filename.nan");
	//{
	//	boost::archive::text_oarchive oa(ofs);
	//	oa << dilionPawn;
	//}
	//
	//delete dilionPawn;
	//dilionPawn = NULL;

	//dilionPawn = new GameObject::Pawn();
	//{
	//	std::ifstream ifs("filename.nan");
	//	boost::archive::text_iarchive ia(ifs);
	//	ia & dilionPawn;
	//}

	g_windowManager->AddGameObject(Background);
	g_windowManager->AddGameObject(dilionPawn);
	g_windowManager->AddGameObject(dutchPlayer);

	return true;
}

///-------------------------------------------------
/// UnInitialize main gameobject and windowmanger.
///-------------------------------------------------
void UnInitializeGameObject()
{
	delete g_windowManager;

	SDL_Quit();
}

///-------------------------------------------------
/// Basic game loop logic for events and rendering.
///-------------------------------------------------
void PollEvents()
{
	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				quit = true;
			}

			g_windowManager->Update(&e);
		}

		g_windowManager->Render();
	}
}

int main(int argc, char **argv)
{
	DESCENDANT_UNUSED(argc);
	DESCENDANT_UNUSED(argv);
	if (!InitializeGameObject())
		return 1;

	PollEvents();
	UnInitializeGameObject();

	return 0;
}