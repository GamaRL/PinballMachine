#pragma once

#include "./Material.h"
#include "./Model.h"

#ifdef WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif

class Rocket
{
public:
  static void Initialise();

  Rocket(float x, float y, float z);

  void Render(GLint, GLuint, GLuint);

private:
  static Model Rocket_Model;

  static Material Rocket_Material;

  glm::vec3 _position;
};
