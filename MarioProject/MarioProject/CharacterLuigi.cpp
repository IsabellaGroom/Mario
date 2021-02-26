#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath,
	Vector2D start_position, LevelMap* map) :
	Character(renderer, imagePath, start_position, map)
{
	m_position.x = 200;


}

CharacterLuigi::~CharacterLuigi()
{

}


void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	//Poll for events
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			m_moving_right = true;
			break;
		case SDLK_UP:
			if (m_can_jump)
			{
				Jump(deltaTime);
			}
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
			break;
		}
		break;
	}
	Character::Update(deltaTime, e);
}
