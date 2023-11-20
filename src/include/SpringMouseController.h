#pragma once

#include "./Window.h"
#include "./Spring.h"

class SpringMouseController
{
public:
  SpringMouseController(Window* window, Spring* spring);
  void Handle();
private:
  Window* _window;
  Spring* _spring;
};
