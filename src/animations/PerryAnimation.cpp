#include "../include/PerryAnimation.h"
#include <glm/fwd.hpp>

PerryAnimation::PerryAnimation(Perry* perry, Window* window)
{
  _perry = perry;
  _window = window;
}

void PerryAnimation::HandleKeyboard(float dt)
{
  static bool isPressed = false;
  bool *keys = _window->getsKeys();

  /*if(keys[GLFW_KEY_A])
  {
    _perry->Move(glm::vec3(-1, 0, 0), dt);
  }
  else if(keys[GLFW_KEY_D])
  {
    _perry->Move(glm::vec3(1, 0, 0), dt);
  }
  else if(keys[GLFW_KEY_W])
  {
    _perry->Move(glm::vec3(0, 0, -1), dt);
  }
  else if(keys[GLFW_KEY_S])
  {
    _perry->Move(glm::vec3(0, 0, 1), dt);
  }*/
}
