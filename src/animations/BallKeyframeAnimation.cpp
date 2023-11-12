/*
KeyFrame[0].movBall_x = 0.000000f;
KeyFrame[0].movBall_z = 0.000000f;
KeyFrame[1].movBall_x = 0.000000f;
KeyFrame[1].movBall_z = 0.000000f;
KeyFrame[2].movBall_x = 0.000000f;
KeyFrame[2].movBall_z = 36.000000f;
KeyFrame[3].movBall_x = -30.000000f;
KeyFrame[3].movBall_z = -2.000000f;
KeyFrame[4].movBall_x = 12.000000f;
KeyFrame[4].movBall_z = -27.000000f;
KeyFrame[5].movBall_x = -12.000000f;
KeyFrame[5].movBall_z = 19.000000f;
KeyFrame[6].movBall_x = -23.000000f;
KeyFrame[6].movBall_z = 48.000000f;
KeyFrame[7].movBall_x = 24.000000f;
KeyFrame[7].movBall_z = 48.000000f;
KeyFrame[8].movBall_x = 5.000000f;
KeyFrame[8].movBall_z = -3.000000f;
KeyFrame[9].movBall_x = 2.000000f;
KeyFrame[9].movBall_z = -75.000000f;
KeyFrame[10].movBall_x = 1.999978f;
KeyFrame[10].movBall_z = 0.000015f;*/

#include "BallKeyframeAnimation.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

BallKeyframeAnimation::BallKeyframeAnimation(Ball* ball)
{
  _ball = ball;
  _frameList = std::vector<struct BallKeyFrame>(10);

  _frameList[0].movBall_x = 0.000000f;
  _frameList[0].movBall_z = 0.000000f;
  _frameList[1].movBall_x = 0.000000f;
  _frameList[1].movBall_z = 36.000000f;
  _frameList[2].movBall_x = -30.000000f;
  _frameList[2].movBall_z = -2.000000f;
  _frameList[3].movBall_x = 12.000000f;
  _frameList[3].movBall_z = -27.000000f;
  _frameList[4].movBall_x = -23.000000f;
  _frameList[4].movBall_z = 48.000000f;
  _frameList[5].movBall_x = 24.000000f;
  _frameList[5].movBall_z = 48.000000f;
  _frameList[6].movBall_x = 5.000000f;
  _frameList[6].movBall_z = -3.000000f;
  _frameList[7].movBall_x = 2.000000f;
  _frameList[7].movBall_z = -75.000000f;
  _frameList[8].movBall_x = 1.000000f;
  _frameList[8].movBall_z = -37.000000f;
  _frameList[9].movBall_x = 0.0f;
  _frameList[9].movBall_z = 0.0f;
}

void BallKeyframeAnimation::ResetAnimation()
{
  _playIndex = -1;
  _position = glm::vec3(_frameList[0].movBall_x, 0.0f, _frameList[0].movBall_z);
  _currStep = MAX_STEPS;
}

void BallKeyframeAnimation::Interpolate()
{
	_frameList[_playIndex].movBall_xInc = (_frameList[_playIndex + 1].movBall_x - _frameList[_playIndex].movBall_x) / MAX_STEPS;
	_frameList[_playIndex].movBall_zInc = (_frameList[_playIndex + 1].movBall_z - _frameList[_playIndex].movBall_z) / MAX_STEPS;
}

void BallKeyframeAnimation::Update(float dt)
{
  float time = 0.0f;
  while(time < dt)
  {
    if (_currStep >= MAX_STEPS) //fin de animación entre frames?
    {
      _playIndex++;
      if (_playIndex > _frameList.size() - 2)	//Fin de toda la animación con último frame?
      {
        ResetAnimation();
      }
      else //Interpolación del próximo cuadro
      {
        _position.x = _frameList[_playIndex].movBall_x;
        _position.z = _frameList[_playIndex].movBall_z;
        _currStep = 0; //Resetea contador
        //Interpolar
        Interpolate();
      }
    }
    else
    {
      //Dibujar Animación
      _position.x += _frameList[_playIndex].movBall_xInc;
      _position.z += _frameList[_playIndex].movBall_zInc;
      _currStep++;
    }
    time += FRAME_PERIOD / MAX_STEPS;
  }
  _ball->SetPosition(_position.x, _position.y, _position.z);
}

