#include "../include/PerryAnimation.h"
#include <glm/ext/scalar_constants.hpp>
#include <glm/fwd.hpp>

PerryAnimation::PerryAnimation(Perry* perry, Window* window)
{
  _perry = perry;
  _window = window;
}

void PerryAnimation::HandleKeyboard(float dt)
{
  static bool isPressed = false;
  bool newIsPressed = false;
  bool *keys = _window->getsKeys();

  float pi_2 = glm::pi<float>() / 2.0f;

  if(keys[GLFW_KEY_A])
  {
    newIsPressed = true;
    _perry->SetRotation(pi_2);
  }
  else if(keys[GLFW_KEY_D])
  {
    newIsPressed = true;
    _perry->SetRotation(-pi_2);
  }
  else if(keys[GLFW_KEY_W])
  {
    newIsPressed = true;
    _perry->SetRotation(0.0f);
  }
  else if(keys[GLFW_KEY_S])
  {
    newIsPressed = true;
    _perry->SetRotation(2*pi_2);
  }

  if (newIsPressed != isPressed)
  {
    if(newIsPressed)
    {
      _perry->SetIsMoving(true);
    }
    else
    {
      _perry->SetIsMoving(false);
    }
  }

  isPressed = newIsPressed;
}
