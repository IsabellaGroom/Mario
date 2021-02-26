#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, 
	Vector2D start_position) : 
	Character(renderer, imagePath, start_position)
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
				Jump(deltaTime);
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
	//cout << m_can_jump << endl;
	cout << "Jump: " << m_jumping << endl;
	Character::Update(deltaTime, e);
}