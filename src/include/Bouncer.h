#pragma once

#include "Bouncer.h"
#include "Model.h"
#include <glm/glm.hpp>

class Bouncer
{
public:
  static void Initialise();
  Bouncer(float x, float y, float z, bool rotated);
  void Render(GLint);
private:
  static Model Bouncer_Model;

  glm::vec3 _position;
  bool _rotated;
};
