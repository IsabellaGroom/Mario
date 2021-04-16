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
	virtual void Render();

private:

	bool m_jump;
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_frame_delay;
	int m_current_frame;

	SoundFX* m_jumpFX;
};

#endif
