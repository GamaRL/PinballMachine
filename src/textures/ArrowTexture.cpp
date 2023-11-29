#include "../include/ArrowTexture.h"

#ifdef WIN32
#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

Texture ArrowTexture::Arrow_Texture = Texture("resources/textures/up.tga");
Material ArrowTexture::Arrow_Material = Material();
Mesh ArrowTexture::Arrow_Mesh = Mesh();

void ArrowTexture::Initialise()
{
  Arrow_Texture.LoadTextureA();
  Arrow_Material = Material(4.0, 256);

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

  Arrow_Mesh = Mesh();
  Arrow_Mesh.CreateMesh(vertices, indexes, 32, 12);
}

ArrowTexture::ArrowTexture(float x, float y, float z, float angle)
{
  _position.x = x;
  _position.y = y;
  _position.z = z;

  _angle = angle;
}

void ArrowTexture::Update(float dt)
{
  _offsetv -= 1.0f * dt;
  if (_offsetv <= 0.0)
    _offsetv = 1.0;
}

void ArrowTexture::Render(GLint uniformModel, GLint uniformColor, GLuint specularIntensityLocation, GLuint shininessLocation, GLint uniformTextureOffset) {
  glm::mat4 model;
  auto toffset = glm::vec2(_offsetu, _offsetv);
  auto color = glm::vec3(1.0f, 1.0f, 1.0f);

  model = glm::mat4(1.0);
  model = glm::translate(model, _position);
  model = glm::scale(model, glm::vec3(10.0f, 5.0f, 15.0f));
  model = glm::rotate(model, -glm::radians(_angle), glm::vec3(0.0f, 1.0f, 0.0f));
  glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
  glUniform3fv(uniformColor, 1, glm::value_ptr(color));
  Arrow_Material.UseMaterial(specularIntensityLocation, shininessLocation);
  Arrow_Texture.UseTexture();
  Arrow_Mesh.RenderMesh();
}

