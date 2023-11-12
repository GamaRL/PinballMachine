#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/Material.h"
#include "../include/Model.h"
#include "../include/SpotLight.h"



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

