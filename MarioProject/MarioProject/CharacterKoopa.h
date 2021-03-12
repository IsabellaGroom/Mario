#pragma once
#ifndef _CHARACTER_KOOPA_H
#define _CHARACTER_KOOPA_H
#include "Character.h"


class CharacterKoopa : public Character
{
private:
	float m_movement_speed;
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;

	void FlipRightWayUp();

public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map,
		Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	bool GetInjured() { return m_injured; }
	virtual void Render();
	virtual void Update(float deltatime, SDL_Event e);
};

#endif

