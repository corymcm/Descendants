#include "main.h"

// Fucking linking errors from sdl, main is defined as SDL_Main
// http://stackoverflow.com/questions/24620143/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc
#ifdef main
#undef main
#endif // main


int main(int argc, wchar_t *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Quit();
	return 0;
}