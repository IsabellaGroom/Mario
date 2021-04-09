#include "SoundFX.h"
#include <SDL_mixer.h>
#include <iostream>

SoundFX::SoundFX()
{
	m_effect = nullptr;
}

SoundFX::~SoundFX()
{
	Mix_FreeChunk(m_effect);
}

void SoundFX::Load(std::string path)
{
	m_effect = Mix_LoadWAV(path.c_str());
	if (m_effect == nullptr)
	{
		std::cout << "Failed to load music. Error: " << Mix_GetError() << std::endl;
	}

}

void SoundFX::Play()
{
	Mix_PlayChannel(-1, m_effect, 0);
}


