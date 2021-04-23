#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, 
	Vector2D start_position, LevelMap* map) :
	Character(renderer, imagePath, start_position, map)
{
	m_jumpFX = new SoundFX;
	m_jumpFX->Load("Music/Jump.wav");
	m_jump = false;
	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterMario::~CharacterMario()
{

}

void CharacterMario::Render()
{
	//variable to hold left pos of sprite
	int left = 0.0f;

	//if injured, move left pos to be left pos of
	//2nd image of sprite sheet

	if (m_jump)
		left = m_single_sprite_w;

	//get the portion of the sprtie sheet you want to draw
	//{xPos, yPos, width, height}
	SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect destRect = { (int)(m_position.x),(int)(m_position.y),
	m_single_sprite_w, m_single_sprite_h };
	
//then draw it facing the correct diretion
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	if (m_moving_left)
	{
		m_facing_direction = FACING_LEFT;
	}
	else
	{
		m_facing_direction = FACING_RIGHT;
	}

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
				m_jumpFX->Play();
				m_jump = true;
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

	if (m_jump)
	{
		m_frame_delay += deltaTime;
		if (m_frame_delay >= 0.0f)
		{
	
			if (m_frame_delay >= 500.0f)
			{
				m_jump = false;
				m_frame_delay = ANIMATION_DELAY;
			}
			//reset frame delay count
			
		}
	}

	//cout << m_can_jump << endl;
	//cout << "Jump: " << m_jumping << endl;

}