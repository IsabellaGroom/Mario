#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

Texture2D::~Texture2D()
{
	//Free up memory
	Free();

	m_renderer = nullptr;
}

bool Texture2D::LoadFromFile(std::string path)
{
	//remove memory used for a previous texture
	Free();


	//Load the image
	//c_str() converts string to char array
	SDL_Surface* p_surface = IMG_Load(path.c_str());

	if (p_surface != nullptr)
	{
		//colour key the image to be transparent
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0xFF, 0xFF));


		//create the texture from the pixels on the surface
		m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);

		//check for errors
		if (m_texture == nullptr)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		else
		{
			m_width = p_surface->w;
			m_height = p_surface->h;
		}

		//remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}
	//Return whether the process was successfull
	return m_texture != nullptr;
}
void Texture2D::Free()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
	    m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}
void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle)
{
	//set where to render the texture 
	SDL_Rect renderLocation = { 0,0,m_width,m_height };

	//Render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);
	//last parameter = flip flag
	//none, horizontal, vertical
}

/*
int Texture2D::GetWidth()
{
	return m_width;
}

int Texture2D::GetHeight()
{
	return m_height;
}
*/