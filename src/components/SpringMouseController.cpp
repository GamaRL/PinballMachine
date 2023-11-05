#include "../include/SpringMouseController.h"

SpringMouseController::SpringMouseController(Window* window, Spring* spring)
{
  _window = window;
  _spring = spring;
}

void SpringMouseController::Handle()
{
  if (_window->IsRightButtonPressed())
  {
    _spring->ResetAnimation();
  }
}
