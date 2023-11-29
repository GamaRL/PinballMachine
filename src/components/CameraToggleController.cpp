#include "../include/CameraToggleController.h"
#include <iostream>

CameraToggleController::CameraToggleController(Window* window, Perry* perry)
{
  _window = window;
  _perry = perry;

  _userCamera = Camera(
      glm::vec3(0.0f, 5.0f, 75.0f),
      glm::vec3(0.0f, 1.0f, 0.0f),
      -90.0f,
      0.0f,
      0.0f,
      0.0f);

  _fixedCamera = Camera(
      glm::vec3(0.0f, 170.0f, 160.0f),
      glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)),
      -90.0f,
      -50.0f,
      0.0f, 0.0f);

  _freeCamera = Camera(
      glm::vec3(0.0f, 10.0f, 0.0f),
      glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)),
      -90.0f,
      -50.0f,
      30.0f, 0.5f);

	_userProjection = glm::perspective(45.0f, (GLfloat)window->getBufferWidth() / window->getBufferHeight(), 0.1f, 1000.0f);
  _fixedProjection = glm::perspective(45.0f, (GLfloat)window->getBufferWidth() / window->getBufferHeight(), 0.1f, 1000.0f);
  _freeProjection = glm::perspective(45.0f, (GLfloat)window->getBufferWidth() / window->getBufferHeight(), 0.1f, 1000.0f);
  _selectedCamera = 0;
}

Camera* CameraToggleController::GetCamera()
{
  if(_selectedCamera == 0)
    return &_fixedCamera;
  else if(_selectedCamera == 1)
    return &_userCamera;
  return &_freeCamera;
}

Camera* CameraToggleController::GetUserCamera()
{
  return &_userCamera;
}

glm::mat4* CameraToggleController::GetProjection()
{
  if(_selectedCamera == 0)
    return &_fixedProjection;
  else if(_selectedCamera == 1)
    return &_userProjection;
  return &_freeProjection;
}

void CameraToggleController::HandleKeyBoard(float dt)
{
  static bool is_p_pressed;
  static bool is_o_pressed;
  static bool is_i_pressed;
  bool* keys = _window->getsKeys();

  if (_selectedCamera == 1)
  {
    auto lookAt = _perry->GetLookAt();
    auto position = _perry->GetPosition() -20.0f * lookAt;
    _userCamera.setCameraPosition(position.x, position.y + 5.0f, position.z);
  }
  else if (_selectedCamera == 2)
  {
    _freeCamera.keyControl(_window->getsKeys(), dt);
	  _freeCamera.mouseControl(_window->getXChange(), _window->getYChange());
  }

  if (keys[GLFW_KEY_P])
  {
    is_p_pressed = true;
  }
  else
  {
    if (is_p_pressed == true)
    {
      _selectedCamera = 2;
      is_p_pressed = false;
    }
  }

  if (keys[GLFW_KEY_O])
  {
    is_o_pressed = true;
  }
  else
  {
    if (is_o_pressed == true)
    {
      _selectedCamera = 1;
      is_o_pressed = false;
    }
  }

  if (keys[GLFW_KEY_I])
  {
    is_i_pressed = true;
  }
  else
  {
    if (is_i_pressed == true)
    {
      _selectedCamera = 0;
      is_i_pressed = false;
    }
  }
}

