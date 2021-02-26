#include "PowBlock.h"
#include <iostream>

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* levelMap)
{
	std::string imagePath = "Images/PowBlock.png";
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture." << std::endl;
		return;
	}

	m_level_map = levelMap;
	//there are three images in this sprite sheet in a row
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
	m_num_hits_left = 3;
	m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_w * 0.5, 260);
}

PowBlock::~PowBlock()
{
	m_renderer = nullptr;
	delete m_texture;
	m_texture = nullptr;
}

void PowBlock::Render()
{
	if (m_num_hits_left > 0)
	{
		//position on sprite sheet
		SDL_Rect src = { m_single_sprite_w * m_num_hits_left, 0, m_single_sprite_w, m_single_sprite_h };
		//position in level
		SDL_Rect dst = { m_position.x, m_position.y, m_single_sprite_w, m_single_sprite_h };
		m_texture->Render(src, dst, SDL_FLIP_NONE, 0.0f);
	}

}

void PowBlock::TakeHit()
{
	m_num_hits_left -= 1;

	if (m_num_hits_left <= 0)
	{
		m_num_hits_left = 0;
		m_level_map->ChangeTileAt(8, 7, 0);
		m_level_map->ChangeTileAt(8, 8, 0);
	}
}
