#pragma once
#ifndef _CHARACTER_COIN_H
#define _CHARACTER_COIN_H
#include "Character.h"

class CharacterCoin : public Character
{
private:
	float m_frame_delay;
	int m_current_frame;
	float m_single_sprite_w;
	float m_single_sprite_h;
	
public:

	CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterCoin();
	virtual void Render();
	virtual void Update(float deltatime, SDL_Event e);
};
#endif

