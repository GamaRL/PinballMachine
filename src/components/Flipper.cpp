#include "../include/Flipper.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/trigonometric.hpp>

Model Flipper::Flipper_Izquierdo = Model();
Model Flipper::Flipper_Derecho = Model();
Material Flipper::Flipper_Material;

Flipper::Flipper(float x, float y, float z, int tipo)
{
  this->position = glm::vec3(x, y, z);
  this->_tipo = tipo;
}

void Flipper::Initialise()
{
  Flipper::Flipper_Izquierdo.LoadModel("resources/models/Flipper_Izquierdo.obj");
  Flipper::Flipper_Derecho.LoadModel("resources/models/Flipper_Derecho.obj");
  Flipper::Flipper_Material = Material(0.3f, 4.0f);
}

void Flipper::Render(GLint uniformModel, GLuint specularIntensityLocation, GLuint shininessLocation)
{
  glm::mat4 model;

  model = glm::mat4(1.0);
  model = glm::translate(model, this->position);
  switch(GetTipo())
  {
    case 0:
      model = glm::rotate(model, this->rotation, glm::vec3(0, 1, 0));
      break;
    case 1:
    case 2:
      model = glm::rotate(model, -this->rotation, glm::vec3(0, 1, 0));
  }
  model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));

  if (GetTipo() == 2)
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Flipper_Material.UseMaterial(specularIntensityLocation, shininessLocation);
  switch(GetTipo())
  {
    case 0:
      Flipper_Izquierdo.RenderModel();
      break;
    case 1:
    case 2:
      Flipper_Derecho.RenderModel();
  }
}

void Flipper::Update(int direction, float dt)
{
  const float pi_4 = glm::pi<float>() / 4.0f;
  if (direction == 1)
  {
    // Subida
    if (this->rotation > pi_4)
    {
        this->rotation = pi_4;
    }
    else
    {
      if (this->rotation + 2.0f * dt < pi_4)
      {
        this->rotation = pi_4;
      }
      else
      {
        this->rotation += 2.0f * dt;
      }
    }
  }
  else
  {
    // Bajada
    if (this->rotation < 0.0f)
    {
        this->rotation = 0.0f;
    }
    else
    {
      if (this->rotation - 2.0f * dt < 0.0f)
      {
        this->rotation = 0.0f;
      }
      else
      {
        this->rotation -= 2.0f * dt;
      }
    }
  }
}

int Flipper::GetTipo()
{
  return _tipo;
}
