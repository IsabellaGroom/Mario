#pragma once
#ifndef _CHARACTER_MARIO_H_
#define _CHARACTER_MARIO_H_

#include "Character.h"
#include "SoundFX.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterMario();
	virtual void Update(float deltaTime, SDL_Event e);

	SoundFX* m_jumpFX;
};

#endif
