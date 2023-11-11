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
    switch(flipper->GetTipo())
    {
      case 0:
        flipper->Update(keys[GLFW_KEY_J] ? 1 : 0, dt / n_interpolations);
        break;
      case 1:
        flipper->Update(keys[GLFW_KEY_K] ? 1 : 0, dt / n_interpolations);
        break;
      case 2:
        flipper->Update(keys[GLFW_KEY_L] ? 1 : 0, dt / n_interpolations);
    }
  }
}
