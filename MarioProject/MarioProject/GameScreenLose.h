#pragma once
#ifndef _GAME_SCREEN_LOSE_H
#define _GAME_SCREEN_LOSE_H
#include "GameScreen.h"
#include "Commons.h"

class Texture2D;

class GameScreenLose : GameScreen
{
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
public:
	GameScreenLose(SDL_Renderer* renderer);
	~GameScreenLose();

	void Render() override;
	void Update(float deltaTimer, SDL_Event e)override;

};


#endif

