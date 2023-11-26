#pragma once

#include <AL/al.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

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
