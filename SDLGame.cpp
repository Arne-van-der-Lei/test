#include "stdafx.h"
#include "SDLGame.h"
#include <iostream>
#include <string>

#include "SphereMesh.h"
#include "PlaneMesh.h"


using namespace std;

SDLGame::SDLGame()
{
	if (!InitSDL())
	{
		// TODO what if init fails
		cout << "Failed to initialize!\n";
	}
}

SDLGame::~SDLGame()
{
	//Free resources and close SDL
	CloseSDL();
}

bool SDLGame::InitSDL()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not enabled!";
		}

		//Create window
		m_pWindow = SDL_CreateWindow(
			m_WIndowTitle.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			m_Width,
			m_Height,
			SDL_WINDOW_SHOWN);

		if (m_pWindow == NULL)
		{
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			unsigned int renderFlags = SDL_RENDERER_ACCELERATED;
			if (m_IsVSync) renderFlags |= SDL_RENDERER_PRESENTVSYNC;
			//Create renderer for window
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, renderFlags);
			if (m_pRenderer == NULL)
			{
				cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			//Get window surface
			m_pScreenSurface = SDL_GetWindowSurface(m_pWindow);

			////Initialize PNG loading
			//int imgFlags = IMG_INIT_PNG;
			//if (!(IMG_Init(imgFlags) & imgFlags))
			//{
			//	printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			//	success = false;
			//}
		}
	}
	cout << "Game Initialized." << endl;
	return success;
}

void SDLGame::Run()
{
	// load game resources
	GameInit();

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				KeyDown(e.key.keysym.sym);
				break;
			case SDL_KEYUP:
				KeyUp(e.key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
			{
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				MouseMove(mouseX, mouseY);
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			default:
				break;
			}
		}
		// update the game
		GameUpdate();

		//Clear screen
		SDL_SetRenderDrawColor(m_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(m_pRenderer);
		SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0x00, 0x00, 0xFF);

		// render game
		GameDraw(m_pRenderer);

		//Update screen
		SDL_RenderPresent(m_pRenderer);
	}

	GameEnd();

}

void SDLGame::CloseSDL()
{
	//Destroy window	
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	m_pRenderer = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}

void SDLGame::GameInit()
{
	Int3 test(267, 12, -5);
	test.ClampColor();
	string path = "resources/dae.bmp";
	m_Texture.LoadFromFile(m_pRenderer, path);

	m_pRayTracer = new Raytracer(400,400);
	m_pRayTracer->Init(this->m_pRenderer);

	SphereMesh* sphere = new SphereMesh(16,16,3.0f);
	sphere->SetTransform(0, 0, 4.0f);
	m_pRayTracer->AddMesh(sphere);
	string path2 = "resources/CobbleStone.bmp";
	m_Marble.LoadFromFile(m_pRenderer, path2);
	sphere->SetTexture(&m_Marble);

	PlaneMesh* plane = new PlaneMesh(10);
	string path3 = "resources/Silver.bmp";
	m_CobbleStone.LoadFromFile(m_pRenderer, path3);
	m_pRayTracer->AddMesh(plane);
	plane->SetTexture(&m_CobbleStone);
}

void SDLGame::GameUpdate()
{
	m_pRayTracer->Tick(0.02f);
}

void SDLGame::GameDraw(SDL_Renderer* pRenderer)
{
	SDL_Rect dest;
	dest.x = 20;
	dest.y = 20;
	dest.w = m_pRayTracer->GetWidth();
	dest.h = m_pRayTracer->GetHeight();
	SDL_RenderCopy(pRenderer,m_pRayTracer->GetTexture(), NULL, &dest);
}

void SDLGame::GameEnd()
{

}

void SDLGame::KeyDown(SDL_Keycode keycode)
{
	std::cout << "key down: ";
	std::cout << static_cast<char>(keycode) << endl;
}

void SDLGame::KeyUp(SDL_Keycode keycode)
{
	std::cout << "key up: ";
	std::cout << static_cast<char>(keycode) << endl;
}

void SDLGame::MouseMove(int x, int y)
{
	cout << "MouseMove: x=" << x << " y=" << y << endl;
}


