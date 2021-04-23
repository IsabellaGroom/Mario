#pragma once
#ifndef _GAMESCREEN_LEVEL_2_H_
#define _GAMESCREEN_LEVEL_2_H_
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "LevelMap.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include <vector>
#include "SoundFX.h"
#include "Music.h"
#include "SDL_ttf.h"

class CharacterMario;
class Texture2D;

class GameScreenLevel2 : GameScreen
{
private:
	Texture2D* m_background_texture;
	LevelMap* m_level_map;
	int score;

	//Characters
	CharacterMario* Mario;
	CharacterKoopa* koopa;
	CharacterCoin* coin;
	vector<CharacterKoopa*> m_enemies;
	vector<CharacterCoin*> m_coins;

	//Sound
	SoundFX* m_coinFX;
	SoundFX* m_OverFX;
	Music* m_background;

	//Text
	TTF_Font* t_font = NULL;
	SDL_Color t_colour = { 255,255,255 };
	SDL_Surface* t_message = NULL;
	SDL_Texture* t_texture;
	int t_width = 0;
	int t_height = 0;
	std::string t_text;

	float m_background_yPos;

	bool SetUpLevel();
	void SetLevelMap();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position);
	void GetScore();

public:

	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();
	void Render() override;
	void Update(float deltaTimer, SDL_Event e)override;
};

#endif