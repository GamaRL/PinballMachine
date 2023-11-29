#include "../include/PointTexture.h"

#include <iostream>


#ifdef WIN32
#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

Texture PointTexture::Point_Texture = Texture("resources/textures/point.tga");
Material PointTexture::Point_Material = Material();
Mesh PointTexture::Point_Mesh = Mesh();

void PointTexture::Initialise()
{
  Point_Texture.LoadTextureA();
  Point_Material = Material(4.0, 256);

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

  Point_Mesh = Mesh();
  Point_Mesh.CreateMesh(vertices, indexes, 32, 12);
}

PointTexture::PointTexture(float x, float y, float z)
{
  _position.x = x;
  _position.y = y;
  _position.z = z;

  _angle = 0.0f;
  _accumulatedTime = 0.0f;

  _cambio = 50.0f;
}

void PointTexture::Update(float dt)
{
  _accumulatedTime += dt;

  if (_accumulatedTime >= 1.0f)
  {
    _accumulatedTime -= 1.0f;
    _cambio -= 10.0f;
    if (_cambio <= 20.0f)
      _cambio = 50.0;
  }
}

void PointTexture::Render(GLint uniformModel, GLint uniformColor, GLuint specularIntensityLocation, GLuint shininessLocation, GLint uniformTextureOffset) {
  glm::mat4 model;
  auto toffset = glm::vec2(_offsetu, _offsetv);
  auto color = glm::vec3(1.0f, 1.0f, 1.0f);

  model = glm::mat4(1.0);
	model = glm::translate(model, _position);
	model = glm::scale(model, glm::vec3(_cambio / 5.0f, _cambio / 5.0f, _cambio / 5.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
  Point_Material.UseMaterial(specularIntensityLocation, shininessLocation);
	Point_Texture.UseTexture();
	Point_Mesh.RenderMesh();
}

