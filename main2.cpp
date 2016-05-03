/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/
#include "stdafx.h"
//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
//#include <SDL_image.h>

#include "SDLGame.h"
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")


int main(int argc, char *argv[])
{

	SDLGame sdlGame;
	sdlGame.Run();
	return 0;
}