#include "../include/Listener.h"
#include <AL/al.h>
#include <iostream>

Listener::Listener()
{
  alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
  SetPosition(0.0f, 0.0f, 0.0f);
  alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
}

void Listener::SetPosition(float x, float y, float z)
{
  alListener3f(AL_POSITION, x, y, z);
}
