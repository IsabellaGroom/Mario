#include "Music.h"
#include <iostream>

Music::Music()
{
	m_music = nullptr;
}

Music::~Music()
{
	Mix_FreeMusic(m_music);
	m_music = nullptr;
}

void Music::Load(std::string path)
{
	m_music = Mix_LoadMUS(path.c_str());
	if (m_music == nullptr)
	{
		std::cout << "Failed to load music. Error: " << Mix_GetError() << std::endl;
	}
}

void Music::Play()
{
	//loop
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(m_music, -1);
	}
}

void Music::Stop()
{
	Mix_HaltMusic();
}