
#include <SDL.h>
#include<SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>
using namespace std;

//Globals
SDL_Window* g_window = nullptr;

//Function prototypes
bool InitSDL();
void CloseSDL();

int main(int arc, char* args[])
{
	
	//check if sdl was setup correctly
	if (InitSDL())
	{
		SDL_Delay(5000);
	}

	CloseSDL();

	return 0;
}

bool InitSDL()
{
	//Setup SDL
	//SDL_INIT will return -1 on failiure
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//setup passed so create window
		/*SDL_Create window:
		* 1st- String at top of window
		* 2nd- Screen position X
		* 3rd- Screen position Y
		* using SDL_WINDOWPOS_UNDEFINIED allows to not set a particular position
		* 4th- int width of the window
		* 5th- int height of window
		* Final- flag to state whether the window should be instantly shown
		* 
		* Flags that might be useful:
		* SDL_WINDOW FULLSCREEN
		* SDL_WINDOW INPUT_FOCUS
		* SDL_WINDOW_MOUSE_FOCUS
		*/
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//checks to see if window was created
		if (g_window == nullptr) 
		{
			cout << "Window was not created, Error: " << SDL_GetError();
			return false;
		}
		return true;
	}
}

void CloseSDL()
{
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

}

