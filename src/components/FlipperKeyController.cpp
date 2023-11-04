#include "../include/FlipperKeyController.h"

FlipperKeyController::FlipperKeyController(Window* window)
{
  _window = window;
}

void FlipperKeyController::Handle(Flipper *flipper, float dt)
{
  const int n_interpolations = 10;
  bool* keys = this->_window->getsKeys();

  for(int i = 0; i < n_interpolations; i++)
  {
    if (flipper->GetTipo() == 0)
    {
      flipper->Update(keys[GLFW_KEY_J] ? 1 : 0, dt / n_interpolations);
    }
    else
    {
      flipper->Update(keys[GLFW_KEY_K] ? 1 : 0, dt / n_interpolations);
    }
  }
}
