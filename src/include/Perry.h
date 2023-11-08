#pragma once

#ifdef WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif

#include "./Model.h"

class Perry
{
public:
  static void Initialise();

  Perry(float, float, float);
  void Render(GLint);
private:
  static Model Trunk_Model;
  static Model Hat_Model;
  static Model Tail_Model;
  static Model Shoulder_Model;
  static Model Hand_Model;
  static Model Leg_Model;
  static Model Foot_Model;

  glm::vec3 _position;
  float _angle1;
  float _angle2;
  float _angle3;
  float _angle4;
};
