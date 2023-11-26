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
private:
  int _sourceId;
	ALuint _source;
	float _pitch = 1.f;
	float _gain = 1.f;
  glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 _velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	bool _loopSound = false;
	ALuint _buffer = 0;
};
