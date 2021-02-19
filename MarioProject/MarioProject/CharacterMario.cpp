#include "CharacterMario.h"
#include <iostream>

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, 
	Vector2D start_position, LevelMap* map) :
	Character(renderer, imagePath, start_position, map)
{

}

CharacterMario::~CharacterMario()
{

}


void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	//Poll for events
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_d:
			m_moving_right = true;
			break;
		case SDLK_w:
			if (m_can_jump)
			{
				Jump();
				cout << "JUMP!" << endl;
			}
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = false;
			break;
		case SDLK_d:
			m_moving_right = false;
			break;
		}
		break;
	}
	cout << "Y: " << m_position.y << endl;
	//cout << m_jump_force << endl;
	//cout << m_jumping << endl;
	//cout << m_can_jump << endl;
	Character::Update(deltaTime, e);
}




//jumping always yes
//jump force never reduces
//never goes into first if statement so:
//can jump is always true

