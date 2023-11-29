#pragma once

#include "./Model.h"

#ifdef WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif

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
