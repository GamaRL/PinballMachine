#include "../include/Inador.h"

Model Inador::Inador_Base = Model();
Model Inador::Inador_Cuerpo = Model();
Model Inador::Inador_Punta = Model();

Inador::Inador(float x, float y, float z)
{
  this->position = glm::vec3(x, y, z);
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
  model = glm::translate(model, this->position);
  modelaux = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Inador_Base.RenderModel();

  model = modelaux;
  model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
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
  this->rotation1 += angle;
}

void Inador::Rotate2(float angle)
{
  this->rotation2 += angle;
}
