#pragma once

#include "./Source.h"
#include "./Buffer.h"

class EnvironmentAudioController
{
public:
  EnvironmentAudioController();
  void Play();
private:
  uint32_t _sound;
  Source _source;
};

