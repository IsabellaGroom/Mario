#pragma once
#ifndef _MUSIC_H
#define _MUSIC_H
#include <SDL_Mixer.h>
#include <string>
class Music
{
  public:
	  Music();
	  ~Music();
	  void Load(std::string path);
	  void Play();
	  void Stop();
	  Mix_Music* m_music;
};

#endif
