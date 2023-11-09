#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
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
  _angle1 = 0.0f;
  _angle2 = 0.0f;
  _angle3 = 0.0f;
  _angle4 = 0.0f;
}

void Perry::Render(GLint uniformModel)
{
  // TODO: Agregar animación
  static bool toggle = true;
  static bool toggle2 = false;

  if(_angle3 <= -3.14f / 4.0f)
    toggle = false;
  else if(_angle3 >= 3.14f / 4.0f)
    toggle = true;


  if(toggle)
  {
    RotateRightHand(-0.06f);
    RotateLeftLeg(-0.1f);
  }
  else
  {
    RotateRightHand(0.06f);
    RotateLeftLeg(0.1f);
  }


  if(_angle4 <= -3.14f / 4.0f)
    toggle2 = false;
  else if(_angle4 >= 3.14f / 4.0f)
    toggle2 = true;

  if(toggle2)
  {
    RotateLeftHand(-0.06f);
    RotateRightLeg(-0.1f);
  }
  else
  {
    RotateLeftHand(0.06f);
    RotateRightLeg(0.1f);
  }

  glm::mat4 model, modelaux, modelaux2;

  // Torso
  model = glm::mat4(1.0);
  model = glm::translate(model, _position);
  model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
  model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
  modelaux = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Trunk_Model.RenderModel();

  // Sombrero
  model = modelaux;
  model = glm::translate(model, glm::vec3(0.0f, 0.8f, 0.0f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Hat_Model.RenderModel();

  // Cola
  model = modelaux;
  model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.40f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Tail_Model.RenderModel();

  // Brazo izquierdo
  model = modelaux;
  model = glm::translate(model, glm::vec3(0.45f, 0.0f, 0.0f));
  model = glm::rotate(model, _angle1, glm::vec3(1,0,0));
  model = glm::rotate(model, -1.0f, glm::vec3(0,0,1));
  modelaux2 = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Shoulder_Model.RenderModel();

  model = modelaux2;
  model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f));
  model = glm::rotate(model, glm::pi<float>() * 0.25f, glm::vec3(0,1,0));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Hand_Model.RenderModel();

  // Brazo derecho
  model = modelaux;
  model = glm::translate(model, glm::vec3(-0.45f, 0.0f, 0.0f));
  model = glm::rotate(model, _angle2, glm::vec3(1,0,0));
  model = glm::rotate(model, 1.0f, glm::vec3(0,0,1));
  modelaux2 = model;
  model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Shoulder_Model.RenderModel();

  model = modelaux2;
  model = glm::translate(model, glm::vec3(-0.35f, 0.0f, 0.0f));
  model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
  model = glm::rotate(model, glm::pi<float>() * 0.25f, glm::vec3(0,1,0));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Hand_Model.RenderModel();

  // Pierna izquierda
  model = modelaux;
  model = glm::translate(model, glm::vec3(0.45f, -0.75f, 0.0f));
  model = glm::rotate(model, _angle3, glm::vec3(1, 0, 0));
  modelaux2 = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Leg_Model.RenderModel();

  model = modelaux2;
  model = glm::translate(model, glm::vec3(0.0f, -0.375f, 0.0f));
  if(_angle3 < 0.0f)
    model = glm::rotate(model, _angle3, glm::vec3(1, 0, 0));
  else
    model = glm::rotate(model, -_angle3, glm::vec3(1, 0, 0));
  modelaux2 = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Foot_Model.RenderModel();

  // Pierna derecha
  model = modelaux;
  model = glm::translate(model, glm::vec3(-0.45f, -0.75f, 0.0f));
  model = glm::rotate(model, _angle4, glm::vec3(1, 0, 0));
  modelaux2 = model;
  model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Leg_Model.RenderModel();

  model = modelaux2;
  model = glm::translate(model, glm::vec3(0.0f, -0.375f, 0.0f));
  if(_angle4 < 0.0f)
    model = glm::rotate(model, _angle4, glm::vec3(1, 0, 0));
  else
    model = glm::rotate(model, -_angle4, glm::vec3(1, 0, 0));
  modelaux2 = model;
  model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Foot_Model.RenderModel();
}

void Perry::RotateLeftHand(float delta)
{
  const float pi_3 = glm::pi<float>() * 0.33f;
  if (_angle1 + delta > pi_3)
  {
    _angle1 = pi_3;
  }
  else if (_angle1 + delta < -pi_3)
  {
    _angle1 = 0.0f;
  }
  else
  {
    _angle1 += delta;
  }
}

void Perry::RotateRightHand(float delta)
{
  const float pi_3 = glm::pi<float>() * 0.33f;
  if (_angle2 + delta > pi_3)
  {
    _angle2 = pi_3;
  }
  else if (_angle2 + delta < -pi_3)
  {
    _angle2 = 0.0f;
  }
  else
  {
    _angle2 += delta;
  }
}

void Perry::RotateLeftLeg(float delta)
{
  const float pi_4 = glm::pi<float>() * 0.25f;
  if (_angle3 + delta > pi_4)
  {
    _angle3 = pi_4;
  }
  else if (_angle3 + delta < -pi_4)
  {
    _angle3 = -pi_4;
  }
  else
  {
    _angle3 += delta;
  }
}

void Perry::RotateRightLeg(float delta)
{
  const float pi_4 = glm::pi<float>() * 0.25f;
  if (_angle4 + delta > pi_4)
  {
    _angle4 = pi_4;
  }
  else if (_angle4 + delta < -pi_4)
  {
    _angle4 = -pi_4;
  }
  else
  {
    _angle4 += delta;
  }
}

void Perry::Move(glm::vec3 direction, float dt)
{
  _position += Perry::speed * glm::normalize(direction) * dt;
}

void Perry::SetPosition(float x, float y, float z)
{
  _position.x = x;
  _position.y = y;
  _position.z = z;
}
