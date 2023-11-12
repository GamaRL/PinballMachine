#pragma once
#include "./Ball.h"

#include <vector>
#include <glm/glm.hpp>

struct BallKeyFrame
{
  //Variables para GUARDAR Key Frames
  float movBall_x;      // Posición en X
	float movBall_z;      // Posición en Z
	float movBall_xInc;		// Variable para el incremento en X
	float movBall_zInc;		// Variable para el incremento en Z
};

class BallKeyframeAnimation
{
public:
  static constexpr int MAX_STEPS = 30;
  static constexpr float FRAME_PERIOD = 2.00f;
  static void Initialise();

  BallKeyframeAnimation(Ball* ball);
  void Update(float dt);
  void ResetAnimation();
private:
  void Interpolate();

  glm::vec3 _position;
  Ball* _ball;
  unsigned int _frameIndex;
  unsigned int _playIndex;
  unsigned int _currStep;
  std::vector<struct BallKeyFrame> _frameList;
  bool _isPlaying;
};
