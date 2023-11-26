#include "../include/SpringMouseController.h"
#include "../include/Listener.h"
#include <iostream>

SpringMouseController::SpringMouseController(Window* window, Spring* spring, SpringAudioController *ac)
{
  _window = window;
  _spring = spring;
  _audioController = ac;
}

void SpringMouseController::Handle()
{
  static float p = 0.0f;
  if (_window->IsRightButtonPressed())
  {
    p += 0.5f;
    //Listener::get()->SetPosition(0.0f, 0.0f, p);
    //std::cout << p << std::endl;
    _audioController->Play();
    _spring->ResetAnimation();
  }
}
