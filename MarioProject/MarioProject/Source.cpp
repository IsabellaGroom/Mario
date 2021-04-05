#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
#include <iostream>

using namespace std;

//Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
Mix_Music* g_music = nullptr;


//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void LoadMusic(string path);

int main(int argc, char* args[])
{
	if (InitSDL())
	{

		LoadMusic("Music/Mario.mp3");
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(g_music, -1);
		}

		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);

		//set the time
		g_old_time = SDL_GetTicks();

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

		g_window = SDL_CreateWindow
		(
			"Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

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
		}

		//initialise the mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not init. Error: " << Mix_GetError();
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

	//destroy the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;

	//clear up music
	Mix_FreeMusic(g_music);
	g_music = nullptr;

	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	//prevents double delete errors
	g_renderer = nullptr;
}

bool Update()
{
	//Time
	Uint32 new_time = SDL_GetTicks();

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
		case SDLK_SPACE:
			if (game_screen_manager->GetScreen() == SCREEN_MENU)
			{
				game_screen_manager->ChangeScreen(SCREEN_LEVEL1);
			}
			break;
		}
	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	
	return false;
}

void Render()
{
	//Clear the screen
	//parameters = renderer + 4 hex values for colour of screen
	//0xFF * 4 = white, 0x00 * 4 = black
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();


	//update the screen
	SDL_RenderPresent(g_renderer);

}

void LoadMusic(string path)
{
	g_music = Mix_LoadMUS(path.c_str());
	if (g_music == nullptr)
	{
		cout << "Failed to load music. Error: " << Mix_GetError() << endl;
	}
}

//cleans up any memory used
/*
void FreeTexture()
{
	//check if texture exists before removing it
	if (g_texture != nullptr)
	{
		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;
	}
}
*/

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

