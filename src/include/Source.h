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
private:
  int _sourceId;
  glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
	ALuint _source;
	ALuint _buffer = 0;
};
