#pragma once

#include "./Perry.h"
#include "./Window.h"

class PerryAnimation
{
public:
  PerryAnimation(Perry *, Window *);

  void HandleKeyboard(float);

private:
  float _angle1;
  float _angle2;
  float _angle3;
  float _angle4;

  Window* _window;
  Perry* _perry;
};
