#pragma once

#include "./Material.h"
#include "./Model.h"
#include "./SpotLight.h"

#ifdef WIN32
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif


class Inador
{
public:

  static void Initialise();

  Inador(float x, float y, float z, float orientation, SpotLight* light);
  void Rotate1(float angle);
  void Rotate2(float angle);
  void Render(GLint, GLuint, GLuint);
  void UpdateLight();

private:
  static Model Inador_Base;
  static Model Inador_Cuerpo;
  static Model Inador_Punta;

  static Material Material_Inador;

	glm::vec3 _position;
  float _orientation;
  float _rotation1 = 0.0f;
  float _rotation2 = 0.0f;
  SpotLight* _light;
};

