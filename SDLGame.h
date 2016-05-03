#pragma once
#include <SDL.h>
//#include <SDL_image.h>
#include <string>
#include "Texture.h"
#include "RayTracer.h"

class SDLGame
{
public:
	SDLGame();
	virtual ~SDLGame();
	SDLGame(const SDLGame&) = delete;
	SDLGame& operator=(const SDLGame&) = delete;

	void Run();
	bool InitSDL();
	void CloseSDL();

	void GameInit();
	void GameUpdate();
	void GameDraw(SDL_Renderer* pRenderer);
	void GameEnd();

	void KeyDown(SDL_Keycode keycode);
	void KeyUp(SDL_Keycode keycode);
	void MouseMove(int x, int y);

	// game specific

private:
	int m_Width{ 842 }, m_Height{ 640 };
	bool m_IsVSync = true;
	std::string m_WIndowTitle{ "SDLGame" };

	//The window we'll be rendering to
	SDL_Window* m_pWindow{ nullptr };

	//The window renderer
	SDL_Renderer* m_pRenderer{ nullptr };

	//The surface contained by the window
	SDL_Surface* m_pScreenSurface{ nullptr };

	// Game vars
	int m_Counter{ 0 };

	//The image we will load and show on the screen (stack object!)
	Texture m_Texture;
	Texture m_CobbleStone;
	Texture m_Marble;

	Raytracer* m_pRayTracer;
};

