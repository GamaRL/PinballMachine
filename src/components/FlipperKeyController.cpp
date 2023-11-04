#include "../include/FlipperKeyController.h"

FlipperKeyController::FlipperKeyController(Window* window)
{
  _window = window;
}

void FlipperKeyController::Handle(Flipper *flipper, float dt)
{
  bool* keys = this->_window->getsKeys();

  if (flipper->GetTipo() == 0)
  {
    flipper->Update(keys[GLFW_KEY_J] ? 1 : 0, dt);
  }
  else
  {
    flipper->Update(keys[GLFW_KEY_K] ? 1 : 0, dt);
  }
}
