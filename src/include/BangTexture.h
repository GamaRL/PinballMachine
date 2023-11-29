#pragma once

#include "../include/Texture.h"
#include "../include/Material.h"
#include "../include/Mesh.h"

class BangTexture
{
public:
  static void Initialise();

  void Render(GLint uniformModel, GLint uniformColor, GLuint specularIntensityLocation, GLuint shininessLocation, GLint uniformTextureOffset);
  void Update(float dt);
private:
  static Texture Bang_Texture;
  static Material Bang_Material;
  static Mesh Bang_Mesh;

  float _offsetv = 0.0f;
  float _offsetu = 0.0f;
};
