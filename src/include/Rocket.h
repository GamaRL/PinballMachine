#pragma once

#include <glm/glm.hpp>

#include "Material.h"
#include "Model.h"

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
