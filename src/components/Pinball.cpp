#include "../include/Pinball.h"
#include <glm/fwd.hpp>

#ifdef WIN32
#include <ext/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

Model Pinball::Cover_Model = Model();
Model Pinball::Lever_Model = Model();
Material Pinball::Pinball_Material = Material();

void Pinball::Initialise()
{
	Pinball_Material = Material(6.0f, 27.0f);
  Cover_Model.LoadModel("resources/models/Pinball_Cover.obj");
  Lever_Model.LoadModel("resources/models/Pinball_Lever.obj");
}

Pinball::Pinball(Window *window)
{
  _window = window;
  _isRunning = false;
  _leverT = 0.0f;
  _leverAmplitude = 0.0f;
}

void Pinball::Update(float dt)
{
  if(_isRunning)
  {
    _leverAmplitude -= 10.0f * dt;
    _leverT += dt;

    if (_leverAmplitude < 0.1)
    {
      _isRunning = false;
    }
  }
}

void Pinball::HandleStart()
{
  static bool isPressed = false;
  if (!_isRunning)
  {
    if (_window->IsRightButtonPressed())
    {
      _leverAmplitude = 4.0f;
      _leverT = 0.0f;
      isPressed = true;
    }
    else if (isPressed)
    {
      _isRunning = true;
      isPressed = false;
    }
  }
}

void Pinball::Render(GLint uniformModel, GLuint specularIntensityLocation, GLuint shininessLocation)
{
  glm::mat4 model = glm::mat4(1.0f);
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
  Cover_Model.RenderModel();

  model = glm::translate(model, glm::vec3(47.0f, 0.0f, 95.0f + _leverAmplitude));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
  Lever_Model.RenderModel();
}

