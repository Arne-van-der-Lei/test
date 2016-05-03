#pragma once
#include <string>
#include <SDL.h>
#include "Float2.h"
#include "Int3.h"
//Texture wrapper class
class Texture
{
public:
	Texture();
	virtual ~Texture();
	explicit Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;


	//Loads image at specified path
	bool LoadFromFile(SDL_Renderer* pRenderer, std::string path);

	//Deallocates texture
	void Free();

	//Set color modulation
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void SetBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void SetAlpha(Uint8 alpha);

	//Renders texture at given point
	void Render(SDL_Renderer* pRenderer, int x, int y, SDL_Rect* clip = NULL);

	void Sample(Float2 uv, Int3& color);

	//Gets image dimensions
	int GetWidth();
	int GetHeight();

private:
	//The actual hardware texture
	SDL_Texture* m_pTexture{ nullptr };
	SDL_Surface* m_pSurface{ nullptr };

	//Image dimensions
	int m_Width{ 0 };
	int m_Height{ 0 };
};



