#pragma once
#ifndef _GAMESCREEN_LEVEL1_H
#define _GAMESCREEN_LEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "LevelMap.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include <vector>
#include "SoundFX.h"
#include "Music.h"

class CharacterMario;
class CharacterLuigi;
class Texture2D;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
private:
	//variables
	Texture2D* m_background_texture;
	LevelMap* m_level_map;
	int score;

	//Pow
	PowBlock* m_pow_block;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	//Characters
	CharacterMario* Mario;
	CharacterLuigi* Luigi;
	CharacterKoopa* koopa;
	CharacterCoin* coin;
	vector<CharacterKoopa*> m_enemies;
	vector<CharacterCoin*> m_coins;
	
	//Sound
	SoundFX* m_coinFX;
	SoundFX* m_OverFX;
	Music* m_background;

	//methods
	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenShake();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position);

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTimer, SDL_Event e)override;
	void UpdatePOWBlock();
	void RecordScore(int score);


};

#endif

