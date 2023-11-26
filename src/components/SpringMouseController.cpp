#include "../include/SpringMouseController.h"
#include <iostream>

SpringMouseController::SpringMouseController(Window* window, Spring* spring, SpringAudioController *ac)
{
  _window = window;
  _spring = spring;
  _audioController = ac;
}

void SpringMouseController::Handle()
{
  if (_window->IsRightButtonPressed())
  {
    _audioController->Play();
    _spring->ResetAnimation();
  }
}
