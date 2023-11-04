#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../include/Window.h"
#include "../include/Camera.h"

class CameraToggleController
{
public:
  CameraToggleController(Window* window);
  Camera* GetCamera();
  glm::mat4* GetProjection();
  void HandleKeyBoard();
private:
  Camera _fixedCamera;
  Camera _userCamera;
  glm::mat4 _fixedProjection;
  glm::mat4 _userProjection;
  Window* _window;
  int _selectedCamera;
};
