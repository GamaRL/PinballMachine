#pragma once

#include "./Material.h"
#include "./Model.h"

#ifdef WIN32
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

class Flipper
{
public:

  static void Initialise();

  Flipper(float x, float y, float z, int type);
  void Update(int direction, float dt);
  void Render(GLint, GLuint, GLuint);
  int GetTipo();

private:
  static Model Flipper_Derecho;
  static Model Flipper_Izquierdo;
  static Material Flipper_Material;

	glm::vec3 position;
  int _tipo;
  float rotation = 0.0f;
};


