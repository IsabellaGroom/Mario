#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map)
	: Character(renderer, imagePath, start_position, map)
{
	m_position = start_position;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterCoin::~CharacterCoin()
{

}

void CharacterCoin::Render()
{
	//get the portion of the sprtie sheet you want to draw
	//{xPos, yPos, width, height}
	SDL_Rect portion_of_sprite = {m_single_sprite_w * m_current_frame, 0, m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect destRect = { (int)(m_position.x),(int)(m_position.y),
	m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
}

void CharacterCoin::Update(float deltatime, SDL_Event e) 
{
	m_frame_delay -= deltatime;
	if (m_frame_delay <= 0.0f)
	{
		//reset frame delay count
		m_frame_delay = ANIMATION_DELAY;

		//move the frame over
		m_current_frame++;

		//loop frame around if it goes beyond
		//the number of frames
		if (m_current_frame > 2)
			  m_current_frame = 0;
	}

}
