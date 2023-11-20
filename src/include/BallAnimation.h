#pragma once

#include "./Ball.h"
#include "./Window.h"

#ifdef WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif

class BallAnimation
{
public:
  BallAnimation(Ball *ball, Window *window);
  void HandleStart();
  void Update(float);
private:
  Ball *_ball;
  Window *_window;

  glm::vec3 _position;
  glm::vec3 _velocity;

  bool _isRunning;
  bool _states[9];

  void Reset();
};
