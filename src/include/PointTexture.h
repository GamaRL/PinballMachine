#pragma once

#include "../include/Texture.h"
#include "../include/Material.h"
#include "../include/Mesh.h"

#ifdef WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif

class PointTexture
{
public:
  static void Initialise();

  PointTexture(float x, float y, float z);

  void Render(GLint uniformModel, GLint uniformColor, GLuint specularIntensityLocation, GLuint shininessLocation, GLint uniformTextureOffset);
  void Update(float dt);

private:
  static Texture Point_Texture;
  static Material Point_Material;
  static Mesh Point_Mesh;

  float _offsetv = 0.0f;
  float _offsetu = 0.0f;
  glm::vec3 _position = glm::vec3(0.0f);

  float _angle = 0.0f;
  float _accumulatedTime = 0.0f;

  float _cambio;
};

