#pragma once

#include "../include/Window.h"
#include "../include/Camera.h"
#include "../include/Perry.h"

#ifdef WIN32
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

class CameraToggleController
{
public:
  CameraToggleController(Window* window, Perry* perry);
  Camera* GetCamera();
  Camera* GetUserCamera();
  int GetCameraType() { return _selectedCamera; }
  glm::mat4* GetProjection();
  void HandleKeyBoard(float);
private:
  Camera _fixedCamera;
  Camera _userCamera;
  Camera _freeCamera;
  glm::mat4 _fixedProjection;
  glm::mat4 _userProjection;
  glm::mat4 _freeProjection;
  Window* _window;
  Perry* _perry;
  int _selectedCamera; // 0->fija; 1->personaje; 2->recorrido
};
