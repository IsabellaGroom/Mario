#pragma once
#ifndef _GAMESCREEN_LEVEL1_H
#define _GAMESCREEN_LEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "LevelMap.h"

class CharacterMario;
class CharacterLuigi;
class Texture2D;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
private:
	//variables
	Texture2D* m_background_texture;
	CharacterMario* Mario;
	CharacterLuigi* Luigi;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;

	//methods
	bool SetUpLevel();
	void SetLevelMap();

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTimer, SDL_Event e)override;
	void UpdatePOWBlock();

};

#endif

