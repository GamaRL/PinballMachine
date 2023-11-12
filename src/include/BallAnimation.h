#pragma once
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include "Ball.h"
#include "Window.h"

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
