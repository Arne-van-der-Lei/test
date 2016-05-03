#include "stdafx.h"
#include "Texture.h"
#include <iostream>



Texture::Texture()
{
}


Texture::~Texture()
{
	Free();
}

bool Texture::LoadFromFile(SDL_Renderer* pRenderer, std::string path)
{
	//Get rid of preexisting texture
	Free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	m_pSurface = SDL_LoadBMP(path.c_str());
	if (m_pSurface == NULL)
	{
		std::cout << "Unable to load image %s! SDL Error: " << path.c_str() << SDL_GetError() << std::endl;
	}
	else
	{
		//Color key image
		SDL_SetColorKey(m_pSurface, SDL_TRUE, SDL_MapRGB(m_pSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(pRenderer, m_pSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_Width = m_pSurface->w;
			m_Height = m_pSurface->h;
		}

		//Get rid of old loaded surface
		
	}

	//Return success
	m_pTexture = newTexture;
	return m_pTexture != nullptr;
}

void Texture::Free()
{
	SDL_FreeSurface(m_pSurface);
	//Free texture if it exists
	if (m_pTexture != nullptr)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
		m_Width = 0;
		m_Height = 0;
	}


}

void Texture::Sample(Float2 uv,Int3& color) {
	int bpp = m_pSurface->format->BytesPerPixel;
	uv.Saturate();
	/* Here p is the address to the pixel we want to retrieve */
	int x = ((int)(uv.x * m_Width));
	int y = ((int)(uv.y * m_Height));
	Uint8 *p = (Uint8 *)m_pSurface->pixels + y * m_pSurface->pitch + x * bpp;

	color.x = p[0];
	color.y = p[1];
	color.z = p[2];
}

void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(m_pTexture, red, green, blue);
}

void Texture::SetBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(m_pTexture, blending);
}

void Texture::SetAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(m_pTexture, alpha);
}

void Texture::Render(SDL_Renderer* pRenderer, int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_Width, m_Height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(pRenderer, m_pTexture, clip, &renderQuad);
}

int Texture::GetWidth()
{
	return m_Width;
}

int Texture::GetHeight()
{
	return m_Height;
}