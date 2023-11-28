#pragma once

#include "../include/Texture.h"
#include "../include/Material.h"
#include "../include/Mesh.h"
#include <glm/glm.hpp>

class ArrowTexture
{
public:
  static void Initialise();

  ArrowTexture(float x, float y, float z, float angle);

  void Render(GLint uniformModel, GLint uniformColor, GLuint specularIntensityLocation, GLuint shininessLocation, GLint uniformTextureOffset);
  void Update(float dt);
private:
  static Texture Arrow_Texture;
  static Material Arrow_Material;
  static Mesh Arrow_Mesh;

  float _offsetv = 0.0f;
  float _offsetu = 0.0f;
  glm::vec3 _position = glm::vec3(0.0f);
  float _angle = 0.0f;
};
