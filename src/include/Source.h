#pragma once

#include <AL/al.h>

#ifdef WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif

class Source
{
public:
  Source();
  ~Source();

  void Play(ALuint buffer);
  void SetLoop(bool loop);
  void SetPitch(float pitch);
  void SetPosition(float x, float y, float z);
private:
  int _sourceId;
	ALuint _source;
	ALuint _buffer = 0;
};
