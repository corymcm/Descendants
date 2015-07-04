#include "stdafx.h"
#include "main.h"
#include "WindowManager.h"

// Fucking linking errors from sdl, main is defined as SDL_Main
// http://stackoverflow.com/questions/24620143/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc
#ifdef main
	#undef main
#endif 


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

	WindowManger::WindowManger* window = new WindowManger::WindowManger("Hello World!", 100, 100, 640, 480);

	SDL_Renderer* renderer = window->CreateRenderer();
	if (renderer == nullptr)
	{
		LogError("Error: Failed to create renderer : ");
		window->~WindowManger();
		delete window;
		return false;
	}


	return true;
}

///-------------------------------------------------
/// UnInitialize main gameobject and windowmanger.
///-------------------------------------------------
void UnInitializeGameObject()
{
	SDL_Quit();
}


int main(int argc, wchar_t *argv[])
{
	if (!InitializeGameObject())
		return 1;

	UnInitializeGameObject();

	return 0;
}