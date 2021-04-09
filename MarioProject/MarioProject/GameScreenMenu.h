#pragma once
#ifndef _GAMESCREEN_MENU_H
#define _GAMESCREEN_MENU_H
#include "GameScreen.h"
#include "Commons.h"
#include "Music.h"

class Texture2D;

class GameScreenMenu : GameScreen
{
private:
	Texture2D* m_background_texture;
	Music* m_background_music;
	bool SetUpLevel();
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render() override;
	void Update(float deltaTimer, SDL_Event e)override;
};

#endif
