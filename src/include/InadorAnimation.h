#pragma once
#include "./Inador.h"

class InadorAnimation
{
  public:
    InadorAnimation(Inador *inador);
    void Update(float dt);
  private:
    Inador* _inador;
    float _time;
    float _angle1;
    float _angle2;
};

