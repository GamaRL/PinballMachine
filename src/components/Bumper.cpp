#include "Bumper.h"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Model Bumper::Bumper_Model = Model();

void Bumper::Initialise()
{
  Bumper_Model.LoadModel("resources/models/Bumper.obj");
}

Bumper::Bumper(float x, float y, float z, float scale)
{
  _position = glm::vec3(x, y, z);
  _scale = scale;
}

void Bumper::Render(GLint uniformModel)
{
  glm::mat4 model;
  model = glm::mat4(1.0f);
  model = glm::translate(model, _position);
  model = glm::scale(model, glm::vec3(_scale, 1.0f, _scale));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
  Bumper_Model.RenderModel();
}

