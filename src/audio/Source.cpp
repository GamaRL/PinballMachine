#include "../include/Source.h"
#include <iostream>

Source::Source()
{
  alGenSources(1, &_source);
  alSourcef(_source, AL_ROLLOFF_FACTOR, 1.0f);
  alSourcef(_source, AL_REFERENCE_DISTANCE, 6.0f);
  alSourcef(_source, AL_MAX_DISTANCE, 50.0f);
  alSource3f(_source, AL_POSITION, _position.x, _position.y, _position.y);
  alSource3f(_source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
  alSourcei(_source, AL_LOOPING, _loopSound);
  alSourcei(_source, AL_BUFFER, _buffer);
}

Source::~Source()
{
  alDeleteSources(1, &_source);
}

void Source::Play(const ALuint buffer_to_play)
{
  if (buffer_to_play != _buffer)
  {
    _buffer = buffer_to_play;
    alSourcei(_source, AL_BUFFER, (ALint)_buffer);
  }

  alSourcePlay(_source);


  ALint state = AL_PLAYING;
  alGetSourcei(_source, AL_SOURCE_STATE, &state);
}
