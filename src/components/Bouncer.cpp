#include "../include/Bouncer.h"

#ifdef WIN32
#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

Model Bouncer::Bouncer_Model = Model();

void Bouncer::Initialise()
{
  Bouncer_Model.LoadModel("resources/models/Bouncer.obj");
}

Bouncer::Bouncer(float x, float y, float z, bool rotated)
{
  _position = glm::vec3(x, y, z);
  _rotated = rotated;
}

void Bouncer::Render(GLint uniformModel)
{
  glm::mat4 model;
  model = glm::mat4(1.0f);
  model = glm::translate(model, _position);
  if (_rotated)
    model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
  model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.5f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
  Bouncer_Model.RenderModel();
}
