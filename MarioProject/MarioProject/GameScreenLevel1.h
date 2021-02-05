#pragma once
#ifndef _GAMESCREEN_LEVEL1_H
#define _GAMESCREEN_LEVEL1_H
#include "GameScreen.h"
#include "Commons.h"

class Texture2D;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTimer, SDL_Event e)override;

};

#endif

