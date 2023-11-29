#pragma once
#include "./Model.h"

#include <vector>

#ifdef WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif

struct EarthKeyFrame
{
  //Variables para GUARDAR Key Frames
	float rotation1;		//Variable para IncrementoY
	float rotation2;		//Variable para IncrementoY
	float rotation1_Inc;		//Variable para IncrementoY
	float rotation2_Inc;		//Variable para IncrementoY
};

class Earth
{
public:
  static constexpr int MAX_STEPS = 20;
  static constexpr float FRAME_PERIOD = 3.00f;
  static void Initialise();

  Earth(float x, float y, float z);
  void Animate(float dt);
  void ResetAnimation();
  void Render(GLint uniformModel);
private:
  static Model Earth_Model;
  static Model Moon_Model;
  static Model Base_Model;

  void Interpolate();

  glm::vec3 _position;
  float _rotation1;
  float _rotation2;
  unsigned int _frameIndex;
  unsigned int _playIndex;
  unsigned int _currStep;
  float _accumulatedTime;
  std::vector<struct EarthKeyFrame> _frameList;
  bool _isPlaying;
};
