#pragma once

#include "./Window.h"
#include "./Spring.h"
#include "./SpringAudioController.h"

class SpringMouseController
{
public:
  SpringMouseController(Window* window, Spring* spring, SpringAudioController *ac);
  void Handle();
private:
  Window* _window;
  Spring* _spring;
  SpringAudioController* _audioController;
};
