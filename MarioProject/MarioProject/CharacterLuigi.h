#pragma once
#ifndef _CHARACTER_LUIGI_H_
#define _CHARACTER_LUIGI_H_

#include "Character.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~CharacterLuigi();
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif