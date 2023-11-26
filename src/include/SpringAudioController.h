#pragma once

#include "./Source.h"
#include "./Buffer.h"

class SpringAudioController
{
public:
  SpringAudioController();
  void Play();
private:
  uint32_t _sound;
  Source _source;
};

