#include "stdafx.h"
#include "main.h"
#include "WindowManager.h"

// Fucking linking errors from sdl, main is defined as SDL_Main
// http://stackoverflow.com/questions/24620143/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc
#ifdef main
	#undef main
#endif 

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

	std::string dilion;
	char* imagePath = SDL_GetBasePath();

	dilion = imagePath;
	dilion.append("..\\Descendants\\Textures\\Dilion.bmp");
	SDL_free(imagePath);

	g_windowManager = new WindowManger::WindowManger("You son of a bitch!", 100, 100, 640, 480);
	g_windowManager->LoadTexture(dilion.c_str());

	return true;
}

///-------------------------------------------------
/// UnInitialize main gameobject and windowmanger.
///-------------------------------------------------
void UnInitializeGameObject()
{
	g_windowManager->~WindowManger();
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
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				quit = true;
			}
		}

		g_windowManager->Update();
	}
}

int main(int argc, wchar_t *argv[])
{
	if (!InitializeGameObject())
		return 1;

	PollEvents();
	UnInitializeGameObject();

	return 0;
}