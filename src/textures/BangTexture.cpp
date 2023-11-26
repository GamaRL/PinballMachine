#include "../include/BangTexture.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Texture BangTexture::Bang_Texture = Texture("resources/textures/stroke.tga");
Material BangTexture::Bang_Material = Material();
Mesh BangTexture::Bang_Mesh = Mesh();

void BangTexture::Initialise()
{
  Bang_Texture.LoadTextureA();
  Bang_Material = Material(4.0, 256);

  GLfloat vertices[] = {
    -70.0f, 0.0f, -50.0f,	0.0f, 0.31f,	0.0f, -1.0f, 0.0f,
    70.0f, 0.0f, -50.0f,	1.0f, 0.31f,	0.0f, -1.0f, 0.0f,
    -70.0f, 0.0f, 50.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
    70.0f, 0.0f, 50.0f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f
  };

  unsigned int indexes[] = {
    0, 2, 1,
    1, 2, 3
  };
  Bang_Mesh = Mesh();
  Bang_Mesh.CreateMesh(vertices, indexes, 32, 12);
}

void BangTexture::Update(float dt)
{
  static float accumulatedTime = 0.0f;
  accumulatedTime += dt;

  if (accumulatedTime >= 1.0f)
  {
    accumulatedTime -= 1.0f;
    _offsetv += 0.33886f;
    if (_offsetv >= 1.0)
      _offsetv = 0.0;
  }
}

void BangTexture::Render(GLint uniformModel, GLint uniformColor, GLuint specularIntensityLocation, GLuint shininessLocation, GLint uniformTextureOffset) {
  glm::mat4 model;
  auto toffsetb = glm::vec2(_offsetu, _offsetv);
  auto color = glm::vec3(1.0f, 1.0f, 1.0f);

  model = glm::mat4(1.0);
  model = glm::translate(model, glm::vec3(2.0f, 0.0f, 70.0f));
  model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.2f));
  glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffsetb));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
  glUniform3fv(uniformColor, 1, glm::value_ptr(color));
  BangTexture::Bang_Texture.UseTexture();
  Bang_Material.UseMaterial(specularIntensityLocation, shininessLocation);
  Bang_Mesh.RenderMesh();
}
