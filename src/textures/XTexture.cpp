#include "../include/XTexture.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Texture XTexture::X_Texture = Texture("resources/textures/x.jpeg");
Material XTexture::X_Material = Material();
Mesh XTexture::X_Mesh = Mesh();

void XTexture::Initialise()
{
  X_Texture.LoadTextureA();
  X_Material = Material(4.0, 256);

	unsigned int indexes[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat vertices[] = {
		-0.5f, 0.0f, -0.5f,	0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,	1.0f, 1.0f,	0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, 0.5f,	0.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,	0.0f, -1.0f, 0.0f

	};

  X_Mesh = Mesh();
  X_Mesh.CreateMesh(vertices, indexes, 32, 12);
}

XTexture::XTexture(float x, float y, float z, bool clockwise)
{
  _position.x = x;
  _position.y = y;
  _position.z = z;

  _angle = 0.0f;
  _accumulatedTime = 0.0f;
  _clockwise = clockwise;
}

void XTexture::Update(float dt)
{
  _accumulatedTime += dt;

  if (_accumulatedTime >= 1.0f)
  {
    _accumulatedTime -= 1.0f;
    if (_clockwise)
    {
      _angle += 60.0f;
      if (_angle >= 360.0f)
        _angle -= 360.0f;
    }
    else
    {
      _angle -= 60.0f;
      if (_angle <= 360.0f)
        _angle += 360.0f;
    }
  }
}

void XTexture::Render(GLint uniformModel, GLint uniformColor, GLuint specularIntensityLocation, GLuint shininessLocation, GLint uniformTextureOffset) {
  glm::mat4 model;
  auto toffset = glm::vec2(_offsetu, _offsetv);
  auto color = glm::vec3(1.0f, 1.0f, 1.0f);

  model = glm::mat4(1.0);
  model = glm::translate(model, _position);
  model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
  model = glm::rotate(model, glm::radians(_angle), glm::vec3(0, 1, 0));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
  glUniform3fv(uniformColor, 1, glm::value_ptr(color));
  glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
  X_Material.UseMaterial(specularIntensityLocation, shininessLocation);
  X_Texture.UseTexture();
  X_Mesh.RenderMesh();
}

