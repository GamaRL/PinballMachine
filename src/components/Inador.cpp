#include "../include/Inador.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/fwd.hpp>

Model Inador::Inador_Base = Model();
Model Inador::Inador_Cuerpo = Model();
Model Inador::Inador_Punta = Model();

Inador::Inador(float x, float y, float z, float orientation)
{
  _position = glm::vec3(x, y, z);
  _orientation = orientation;
}

void Inador::Initialise()
{
  Inador::Inador_Base.LoadModel("resources/models/Inador_Base.obj");
  Inador::Inador_Cuerpo.LoadModel("resources/models/Inador_Cuerpo.obj");
  Inador::Inador_Punta.LoadModel("resources/models/Inador_Punta.obj");
}

void Inador::Render(GLint uniformModel)
{
  glm::mat4 model, modelaux;

  model = glm::mat4(1.0);
  model = glm::translate(model, this->_position);
  model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
  model = glm::rotate(model, _rotation1 + _orientation, glm::vec3(0, 1, 0));
  modelaux = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Inador_Base.RenderModel();

  model = modelaux;
  model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
  model = glm::rotate(model, _rotation2, glm::vec3(0, 0, 1));
  modelaux = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Inador_Cuerpo.RenderModel();

  model = modelaux;
  model = glm::translate(model, glm::vec3(-6.5f, 0.0f, 0.0f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Inador_Punta.RenderModel();
}

void Inador::Rotate1(float angle)
{
  const float pi_2 = glm::pi<float>() / 2.0f;
  if (this->_rotation1 + angle > pi_2)
  {
      this->_rotation1 = pi_2;
  }
  else
  {
    if (this->_rotation1 + angle < -pi_2)
    {
      this->_rotation1 = -pi_2;
    }
    else
    {
      this->_rotation1 += angle;
    }
  }
}

void Inador::Rotate2(float angle)
{
  const float pi_3 = glm::pi<float>() / 6.0f;
  if (this->_rotation2 + angle > pi_3)
  {
      this->_rotation2 = pi_3;
  }
  else
  {
    if (this->_rotation2 + angle < -pi_3)
    {
      this->_rotation2 = -pi_3;
    }
    else
    {
      this->_rotation2 += angle;
    }
  }
}

