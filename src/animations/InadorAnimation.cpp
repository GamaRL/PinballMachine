#include "../include/InadorAnimation.h"

InadorAnimation::InadorAnimation(Inador *inador)
{
  this->_inador = inador;
  this->_angle1 = 0.0f;
  this->_angle2 = 0.0f;
  this->_time = rand() % 5;
}

void InadorAnimation::Update(float dt)
{
  float angle1 = this->_angle1;
  float angle2 = this->_angle2;

  this->_angle1 += cos(_time) * dt;
  this->_angle2 += sin(_time) * dt;

  this->_time += dt;

  this->_inador->Rotate1(this->_angle1 - angle1);
  this->_inador->Rotate2(this->_angle2 - angle2);
}

