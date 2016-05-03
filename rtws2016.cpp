// rtws2016.cpp : Defines the entry point for the console application.
//
//Using SDL, SDL_image, standard IO, math, and strings
#include "stdafx.h"
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
/*
#include "stdafx.h"
#include "Float2.h"
#include "Float3.h"
#include "Float4.h"
#include <iostream>
using namespace std;


int main()
{
	Float2 tc(20, -21);
	tc.Saturate(); // After saturate should be (1,0)
	cout << "Tc : " << tc.x << "," << tc.y << endl;

	Float2 tc2(0.1f, 0.2f);
	tc2.Saturate(); // After saturate should be (0.1,0.2)
	cout << "Tc : " << tc2.x << "," << tc2.y << endl;

	Float3 v1(1,0, 0);
	Float3 v2(0, 1, 0);
	Float3 n;
	Float3::Cross(v1, v2, n);

	cout << "Cross product result " << n.x << "," << n.y << "," << n.z << endl;
	float dp = Float3::Dot(v1, v2);
	cout << "Result of dot product: " << dp << endl;

	Float3 n2(0, 0, 1);
	Float3 d(-1, -1, -2);
	Float3 result;
	Float3::Reflect(d, n2, result);

	cout << "Reflected" << result.x << "," << result.y << "," << result.z<<endl;

	float h = Float3::Dot(d, n2);
	Float3 reflected = d - 2 * h * n2;

	Float4 f41(2, 3, 4, -1);
	Float4 f42(3, 8, 1, 9);
	float f4dp = Float4::Dot(f41, f42); // f41.Dot(f42);
	cout << "dp4 result " << f4dp << endl;

	Float3 f31(2, 3, 4);
	Float3 f32(3, 8, 1);
	float f3dp = Float4::Dot(f31, -1, f32, 9);
	cout << "dp4 result " << f3dp << endl;

	cin.get();
	return 0;
}
*/
