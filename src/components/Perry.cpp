#ifdef WIN32
#include <ext/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

#include "../include/Perry.h"

Model Perry::Trunk_Model = Model();
Model Perry::Hat_Model = Model();
Model Perry::Tail_Model = Model();
Model Perry::Shoulder_Model = Model();
Model Perry::Hand_Model = Model();
Model Perry::Leg_Model = Model();
Model Perry::Foot_Model = Model();

void Perry::Initialise()
{
  Trunk_Model.LoadModel("resources/models/Perry_Trunk.obj");
  Hat_Model.LoadModel("resources/models/Perry_Hat.obj");
  Tail_Model.LoadModel("resources/models/Perry_Tail.obj");
  Shoulder_Model.LoadModel("resources/models/Perry_Shoulder.obj");
  Hand_Model.LoadModel("resources/models/Perry_Hand.obj");
  Leg_Model.LoadModel("resources/models/Perry_Leg.obj");
  Foot_Model.LoadModel("resources/models/Perry_Foot.obj");
}

Perry::Perry(float x, float y, float z)
{
  _position = glm::vec3(x, y, z);
}

void Perry::Render(GLint uniformModel)
{
  glm::mat4 model, modelaux, modelaux2;

  model = glm::mat4(1.0);
  model = glm::translate(model, _position);
  modelaux = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Trunk_Model.RenderModel();

  model = modelaux;
  model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Hat_Model.RenderModel();

  model = modelaux;
  model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.45f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Tail_Model.RenderModel();

  // Brazo izquierdo
  model = modelaux;
  model = glm::translate(model, glm::vec3(0.45f, 0.0f, 0.0f));
  model = glm::rotate(model, -0.4f, glm::vec3(0,0,1));
  modelaux2 = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Shoulder_Model.RenderModel();

  model = modelaux2;
  model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f));
  modelaux2 = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Hand_Model.RenderModel();

  // Brazo derecho
  model = modelaux;
  model = glm::translate(model, glm::vec3(-0.45f, 0.0f, 0.0f));
  model = glm::rotate(model, 0.4f, glm::vec3(0,0,1));
  modelaux2 = model;
  model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Shoulder_Model.RenderModel();

  model = modelaux2;
  model = glm::translate(model, glm::vec3(-0.35f, 0.0f, 0.0f));
  modelaux2 = model;
  model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Hand_Model.RenderModel();

  // Pierna izquierda
  model = modelaux;
  model = glm::translate(model, glm::vec3(0.45f, -0.75f, 0.0f));
  modelaux2 = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Leg_Model.RenderModel();

  model = modelaux2;
  model = glm::translate(model, glm::vec3(0.0f, -0.375f, 0.0f));
  modelaux2 = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Foot_Model.RenderModel();

  // Pierna derecha
  model = modelaux;
  model = glm::translate(model, glm::vec3(-0.45f, -0.75f, 0.0f));
  modelaux2 = model;
  model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Leg_Model.RenderModel();

  model = modelaux2;
  model = glm::translate(model, glm::vec3(0.0f, -0.375f, 0.0f));
  modelaux2 = model;
  model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Foot_Model.RenderModel();
}
