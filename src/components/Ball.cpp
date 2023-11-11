#include "../include/Ball.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Model Ball::Ball_Model = Model();
Material Ball::Ball_Material = Material();

void Ball::Initialise()
{
	Ball_Material = Material(6.0f, 27.0f);
  Ball_Model.LoadModel("resources/models/Ball.obj");
}

Ball::Ball(float x, float y, float z)
{
  SetPosition(x, y , z);
}

void Ball::SetPosition(float x, float y, float z)
{
  _position = glm::vec3(x, y, z);
}

void Ball::Render(GLint uniformModel, GLuint specularIntensityLocation, GLuint shininessLocation)
{
  glm::mat4 model;
  model = glm::mat4(1.0f);
  model = glm::translate(model, _position);
  model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
  Ball_Material.UseMaterial(specularIntensityLocation, shininessLocation);
  Ball_Model.RenderModel();
}

