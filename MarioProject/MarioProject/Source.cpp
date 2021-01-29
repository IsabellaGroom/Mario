#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include <iostream>
using namespace std;

//Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		bool quit = false;

		//Game Loop
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}

	CloseSDL();
	return 0;
}

bool InitSDL()
{
	//SetupSDL
	//Flags return 0 on success
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//Setup passed

		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		//checks if window was created
		if (g_window == nullptr)
		{
			cout << "Window was not created. Error: " << SDL_GetError;
			return false;
		}
		
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

		if (g_renderer != nullptr)
		{
			int imageFlags = IMG_INIT_PNG;

			//Error handling
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
			else
			{
				//cout << "Renderer could not initialise. Error: " << SDL_GetError();
				//return false;
			}

			//Load the background texture
			g_texture = LoadTextureFromFile("Images/test.bmp");
			if (g_texture == nullptr)
			{
				return false;
			}

		}
	}
	return true;
}

void CloseSDL()
{
	//release window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	//clear the texture
	FreeTexture();
	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	//prevents double delete errors
	g_renderer = nullptr;
}

bool Update()
{
	//Event handler
	SDL_Event e;

	//get events
	SDL_PollEvent(&e);

	//handle the events
	switch (e.type)
	{
		//Click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	case SDL_KEYUP:
		switch(e.key.keysym.sym)
		{
			//Use SDLK for keys
			//quits application when q is pressed
		case SDLK_q:
			return true;
			break;
		}
	}
	return false;
}

void Render()
{
	//Clear the screen
	//parameters = renderer + 4 hex values for colour of screen
	//0xFF * 4 = white, 0x00 * 4 = black
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	//set where to render the texture 
	SDL_Rect renderLocation = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//Render to screen
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);
	//last parameter = flip flag
	//none, horizontal, vertical
	
	//update the screen
	SDL_RenderPresent(g_renderer);
}

SDL_Texture* LoadTextureFromFile(string path)
{
	//remove memory used for a previous texture
	FreeTexture();

	SDL_Texture* p_texture = nullptr;

	//Load the image
	//c_str() converts string to char array
	SDL_Surface* p_surface = IMG_Load(path.c_str());

	if (p_surface != nullptr)
	{
		//create the texture from the pixels on the surface
		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);

		//check for errors
		if (p_texture == nullptr)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}

		//remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}
	//Return the texture
	return p_texture;
}

//cleans up any memory used
void FreeTexture()
{
	//check if texture exists before removing it
	if (g_texture != nullptr)
	{
		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;
	}
}


/*SDL events:
* SDL_QUIT
* SDL_KEYDOWN
* SDL_KEYUP
* SDL_MOUSEMOTION
* SDL_MOUSEBUTTONDOWN
* SDL_MOUSEBUTTONUP
*/

/* Create Window:
* returns pointer
* 1st- string displayed at top of window
* 2nd- screen position X
* 3rd- screen position Y
* Use SDL_WINDOW_UNDEFINED to not set position
* 4th- int width
* 5th- int height
* Final- flag to state whether window should be instantly shown
*
* Useful flags:
* SDL_WINDOW_FULLSCREEN
* SDL_WINDOW_INPUT_FOCUS
* SDL_WINDOW_mOUSE_FOCUS
*/

/*SDL_CreateRenderer
*(window,
*index of rendering driver[-1 initialises the first one supporting flags]
* combination of SDL_RenderFlags)
* Flags:
* SDL_RENDER_
* SOFTWARE renderer = software fallback
* ACCELERATED renderer uses hardware accleration
* PRESENTVSYNC present is synchronized with refresh rate
* TARGETTEXTURE renderer supports rendering to texture
*/

