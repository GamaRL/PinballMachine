#include "../include/PerryAnimation.h"

#ifdef WIN32
#include <ext/scalar_constants.hpp>
#else
#include <glm/ext/scalar_constants.hpp>
#endif

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

  glm::vec3 velocity = glm::vec3(0.0f);

  float pi_2 = glm::pi<float>() / 2.0f;

  if(keys[GLFW_KEY_A])
  {
    newIsPressed = true;
    _perry->SetRotation(pi_2);
    velocity.x = -10.0f;
  }
  else if(keys[GLFW_KEY_D])
  {
    newIsPressed = true;
    _perry->SetRotation(-pi_2);
    velocity.x = 10.0f;
  }
  else if(keys[GLFW_KEY_W])
  {
    newIsPressed = true;
    _perry->SetRotation(0.0f);
    velocity.z = -10.0f;
  }
  else if(keys[GLFW_KEY_S])
  {
    newIsPressed = true;
    _perry->SetRotation(2*pi_2);
    velocity.z = 10.0f;
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

  velocity = velocity * dt;

  if (_perry->IsMoving())
  {
    _perry->Move(velocity.x, velocity.y, velocity.z);
  }

  isPressed = newIsPressed;
}
