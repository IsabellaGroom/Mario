#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include <iostream>
using namespace std;

//Globals
SDL_Window* g_window = nullptr;

//Function Prototypes
bool InitSDL();
void CloseSDL();

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		//Delay uses milliseconds
		SDL_Delay(5000);
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
		/*Setup passed
		* Create Window:
		* returns pointer
		* 1st- string displayed at top of window
		* 2nd- screen position X
		* 3rd- screen position Y
		* Use SDL_WINDOW_UNDEFINED to not set position
		* 4th- int width
		* 5th- int height
		* Final- flag to state whether window should be instantly shown
		* Useful flags:
		* SDL_WINDOW_FULLSCREEN
		* SDL_WINDOW_INPUT_FOCUS
		* SDL_WINDOW_mOUSE_FOCUS
		*/
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
}