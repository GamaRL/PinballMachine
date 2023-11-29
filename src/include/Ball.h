#pragma once

#ifdef WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif

#include "./Material.h"
#include "./Model.h"

class Ball
{
public:
  static void Initialise();

  Ball(float x, float y, float z);
  void SetPosition(float x, float y, float z);
  void Render(GLint, GLuint, GLuint);
private:
  static Model Ball_Model;
  static Material Ball_Material;

  glm::vec3 _position;
};
