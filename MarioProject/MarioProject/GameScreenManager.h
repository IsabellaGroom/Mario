#pragma once
#ifndef _GAMESCREEN_MANAGER_H
#define _GAMESCREEN_MANAGER_H
#include <SDL.h>
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
private:
	SDL_Renderer* m_renderer;
	GameScreen* m_current_screen;
	SCREENS this_screen;
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	SCREENS GetScreen() { return this_screen; }
	void ChangeScreen(SCREENS new_screen);
};

#endif

