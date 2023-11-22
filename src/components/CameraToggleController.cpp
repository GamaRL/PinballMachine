#include "../include/CameraToggleController.h"
#include <iostream>

CameraToggleController::CameraToggleController(Window* window)
{
  _window = window;
  _userCamera = Camera(
      glm::vec3(0.0f, 5.0f, 75.0f),
      glm::vec3(0.0f, 1.0f, 0.0f),
      -90.0f,
      0.0f,
      20.0f,
      0.5f);
  _fixedCamera = Camera(
      glm::vec3(0.0f, 170.0f, 150.0f),
      glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)),
      -90.0f,
      -50.0f,
      0.0f,
      0.0f);

	_userProjection = glm::perspective(45.0f, (GLfloat)window->getBufferWidth() / window->getBufferHeight(), 0.1f, 1000.0f);
  _fixedProjection = glm::perspective(45.0f, (GLfloat)window->getBufferWidth() / window->getBufferHeight(), 0.1f, 1000.0f);
  _selectedCamera = 0;
}

Camera* CameraToggleController::GetCamera()
{
  if(_selectedCamera == 0)
    return &_fixedCamera;
  return &_userCamera;
}

Camera* CameraToggleController::GetUserCamera()
{
  return &_userCamera;
}

glm::mat4* CameraToggleController::GetProjection()
{
  if(_selectedCamera == 0)
    return &_fixedProjection;
  return &_userProjection;
}

void CameraToggleController::HandleKeyBoard(float dt)
{
  static bool is_q_pressed;
  bool* keys = _window->getsKeys();

  _userCamera.keyControl(keys, dt);
  if (_selectedCamera == 1)
  {
	  _userCamera.mouseControl(_window->getXChange(), _window->getYChange());
  }

  if (keys[GLFW_KEY_Q])
  {
    is_q_pressed = true;
  }
  else
  {
    if (is_q_pressed == true)
    {
      _selectedCamera = (_selectedCamera + 1) % 2;
      is_q_pressed = false;
    }
  }
}

