#pragma once

#include "Model.h"
#include <glm/glm.hpp>

class Bumper
{
public:
  static void Initialise();
  Bumper(float x, float y, float z, float scale);
  void Render(GLint);
private:
  static Model Bumper_Model;

  glm::vec3 _position;
  float _scale;
};

