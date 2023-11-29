#pragma once

#ifdef WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif

#include "./Window.h"
#include "./Material.h"
#include "./Model.h"

class Pinball
{
public:
  static void Initialise();

  Pinball(Window*);
  void HandleStart();
  void Update(float);
  void Render(GLint, GLuint, GLuint);
private:
  static Model Cover_Model;
  static Model Lever_Model;
  static Material Pinball_Material;

  Window *_window;
  bool _isRunning;
  float _leverAmplitude;
  float _leverT;
};
