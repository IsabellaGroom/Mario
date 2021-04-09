#pragma once
#ifndef _SOUNDFX_H
#define _SOUNDFX_H
#include <string>
#include <SDL_mixer.h>

class SoundFX
{
public:
	SoundFX();
	~SoundFX();
	void Load(std::string path);
	void Play();

private:
	Mix_Chunk* m_effect;
};

#endif
