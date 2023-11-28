#pragma once

#include "../include/Texture.h"
#include "../include/Material.h"
#include "../include/Mesh.h"

#ifdef WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif

class XTexture
{
public:
  static void Initialise();

  XTexture(float x, float y, float z, bool clockwise);

  void Render(GLint uniformModel, GLint uniformColor, GLuint specularIntensityLocation, GLuint shininessLocation, GLint uniformTextureOffset);
  void Update(float dt);

private:
  static Texture X_Texture;
  static Material X_Material;
  static Mesh X_Mesh;

  float _offsetv = 0.0f;
  float _offsetu = 0.0f;
  glm::vec3 _position = glm::vec3(0.0f);

  float _angle = 0.0f;
  float _accumulatedTime = 0.0f;
  bool _clockwise;
};
