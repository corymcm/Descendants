#include "stdafx.h"

#include "main.h"
#include "WindowManager.h"
#include "GameObject.h"
#include "Pawn.h"
#include "Player.h"


// TODO : Wrap this in a game object
// global objects are ugly, same with the g_ prefix...
WindowManger::WindowManger* g_windowManager;

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

	std::string TexturePath;
	char* imagePath = SDL_GetBasePath();

	TexturePath = imagePath;
	TexturePath.append("..\\..\\..\\Descendants\\Textures\\");
	SDL_free(imagePath);

	g_windowManager = new WindowManger::WindowManger("You son of a bitch!", 100, 100, 640, 480);

	SDL_Texture* background = g_windowManager->LoadTexture(std::string(TexturePath).append("background.bmp").c_str());
	SDL_Texture* dilion = g_windowManager->LoadTexture(std::string(TexturePath).append("dilion.bmp").c_str());
	SDL_Texture* dutch = g_windowManager->LoadTexture(std::string(TexturePath).append("dutch.bmp").c_str());

	GameObject::GameObject* Background = new GameObject::GameObject(background, NULL);

	SDL_Rect* dilion_position = new SDL_Rect{ 200, 200, 64, 64 };
	SDL_Rect* dutch_position = new SDL_Rect{ 50, 200, 64, 64 };
	GameObject::GameObject* dilionPawn = new GameObject::Pawn(dilion, NULL, dilion_position);
	GameObject::GameObject* dutchPlayer = new GameObject::Player(dutch, NULL, dutch_position);

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
	if (!InitializeGameObject())
		return 1;

	PollEvents();
	UnInitializeGameObject();

	return 0;
}