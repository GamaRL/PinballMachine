#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/Material.h"
#include "../include/Model.h"


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


