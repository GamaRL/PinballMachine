#include "../include/Flipper.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>

Model Flipper::Flipper_Izquierdo = Model();
Model Flipper::Flipper_Derecho = Model();

Flipper::Flipper(float x, float y, float z, int tipo)
{
  this->position = glm::vec3(x, y, z);
  this->_tipo = tipo;
}

void Flipper::Initialise()
{
  Flipper::Flipper_Izquierdo.LoadModel("resources/models/Flipper_Izquierdo.obj");
  Flipper::Flipper_Derecho.LoadModel("resources/models/Flipper_Derecho.obj");
}

void Flipper::Render(GLint uniformModel)
{
  glm::mat4 model, modelaux;

  model = glm::mat4(1.0);
  model = glm::translate(model, this->position);
  model = glm::rotate(model, this->GetTipo() == 0 ? this->rotation : -this->rotation, glm::vec3(0, 1, 0));
  modelaux = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  if(this->GetTipo() == 0)
    Flipper_Izquierdo.RenderModel();
  else
    Flipper_Derecho.RenderModel();
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
