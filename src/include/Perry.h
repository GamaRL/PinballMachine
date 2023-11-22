#pragma once

#include "./Model.h"
#include "./Material.h"
#include <glm/fwd.hpp>

#ifdef WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif

class Perry
{
public:
  static constexpr float speed = 10.0f;
  static void Initialise();

  Perry(float, float, float);
  
  void Animate(float);
  void SetPosition(float, float, float);
  glm::vec3 GetPosition();
  void SetRotation(float);
  void RotateLeftHand(float);
  void RotateRightHand(float);
  void RotateLeftLeg(float);
  void RotateRightLeg(float);

  void SetIsMoving(bool);
  bool IsMoving();
  void Move(float, float, float);
  void SetLookAt(float, float, float);
  glm::vec3 GetLookAt();

  void Render(GLint, GLuint, GLuint);

private:
  static Model Trunk_Model;
  static Model Hat_Model;
  static Model Tail_Model;
  static Model Shoulder_Model;
  static Model Hand_Model;
  static Model Leg_Model;
  static Model Foot_Model;

  static Material Material_Perry;

  glm::vec3 _position;
  glm::vec3 _lookAt;
  bool _isMoving;
  float _rotation;
  float _angle1;
  float _angle2;
  float _angle3;
  float _angle4;
};
