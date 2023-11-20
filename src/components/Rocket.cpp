#include "../include/Rocket.h"

#ifdef WIN32
#include <ext/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

Model Rocket::Rocket_Model = Model();

Material Rocket::Rocket_Material = Material();

Rocket::Rocket(float x, float y, float z)
{
  _position = glm::vec3(x, y, z);
}

void Rocket::Initialise()
{
  Rocket_Model.LoadModel("resources/models/Rocket.obj");
  Rocket_Material = Material(2.0f, 1.0f);
}

void Rocket::Render(GLint uniformModel, GLuint specularIntensityLocation, GLuint shininessLocation)
{
  glm::mat4 model;

  Rocket_Material.UseMaterial(specularIntensityLocation, shininessLocation);

  model = glm::mat4(1.0);
  model = glm::translate(model, _position);
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
  Rocket_Material.UseMaterial(specularIntensityLocation, shininessLocation);

  Rocket_Model.RenderModel();
}
