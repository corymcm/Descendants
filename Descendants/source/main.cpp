#include "stdafx.h"

#include <fstream>
#include <unordered_map> 

#include "main.h"
#include "WindowManager.h"
#include "World.h"
#include "Pawn.h"
#include "Player.h"
#include "PlayerSpawner.h"
#include "WorldManager.h"
#include "SDL_SoundManager.h"
#include "SDL_PlayerController.h"

// TODO : Wrap this in a game object
// global objects are ugly, same with the g_ prefix...
WindowManger::WindowManger* g_windowManager;
WorldManager::WorldManager* g_worldManager;
std::unordered_map<std::string, Controllers::SDL_PlayerController*> g_playerControllers;

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

	std::string dataFolder = SDL_GetBasePath();
	dataFolder.append("..\\..\\..\\Data\\");

	g_windowManager = new WindowManger::WindowManger("You son of a bitch!", 100, 100, 640, 480);
	SoundManager::SDL_SoundManager* soundManager = new SoundManager::SDL_SoundManager(dataFolder + std::string("Sounds\\"));
	g_playerControllers = std::unordered_map<std::string, Controllers::SDL_PlayerController*>();

	Controllers::SDL_PlayerController* pc = new Controllers::SDL_PlayerController();
	g_playerControllers["keyboard"] = pc;

// 	Framework::Rect* dilion_position = new Framework::Rect{ 200, 200, 64, 64 };
// 	Framework::Rect* dutch_position = new Framework::Rect{ 50, 200, 64, 64 };
// 
// 	Framework::ISpawner* player_spawner = new Framework::PlayerSpawner("dutch.bmp", "keyboard", NULL, dutch_position, 5);
// 
// 	Framework::World* test = new Framework::World("TestWorld.nan");
// 	test->SetBackgroundMusic("VietnamJungleThemeRambo.ogg");
// 
// 	Framework::GameObject* Background = new Framework::GameObject("background.bmp", NULL, NULL);
// 	Framework::GameObject* dilionPawn = new Framework::Pawn("dilion.bmp", NULL, dilion_position);
// 	//Framework::GameObject* dutchPlayer = new Framework::Player("dutch.bmp", NULL, dutch_position, "keyboard", 5);
// 
// 	test->AddObject(Background);
// 	test->AddObject(dilionPawn);
// 	test->AddSpawner(player_spawner);
// 
// 	WorldManager::WorldManager* worldManager = new WorldManager::WorldManager(dataFolder, soundManager, test);
// 	worldManager->SaveWorld();

	g_worldManager = new WorldManager::WorldManager(dataFolder, soundManager);
	g_worldManager->LoadWorld("TestWorld.nan");
	g_worldManager->SetWorldControllers(g_playerControllers);

	//Serialization test
// 	std::ofstream ofs("filename.nan");
// 	{
// 		boost::archive::text_oarchive oa(ofs);
// 		oa << dilionPawn;
// 	}
// 
// 	delete dilionPawn;
// 	dilionPawn = NULL;
// 
// 	dilionPawn = new Framework::Pawn();
// 	{
// 		std::ifstream ifs("filename.nan");
// 		boost::archive::text_iarchive ia(ifs);
// 		ia & dilionPawn;
// 	}

// 	g_windowManager->AddGameObject(Background);
// 	g_windowManager->AddGameObject(dilionPawn);
// 	g_windowManager->AddGameObject(dutchPlayer);

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
			for (const auto& pc : g_playerControllers)
			{
				pc.second->AddEvent(&e);
			}

			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				quit = true;
			}
			g_windowManager->Update(&e);
			g_worldManager->UpdateWorld();
		}
		g_worldManager->RenderWorld(g_windowManager->GetRenderer());
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