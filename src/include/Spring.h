#pragma once
#include "./Model.h"

#include <vector>
#include <glm/glm.hpp>

struct SpringKeyFrame
{
  //Variables para GUARDAR Key Frames
	float scaleBall_z;		//Variable para IncrementoY
	float scaleBall_zInc;		//Variable para IncrementoY
};

class Spring
{
public:
  static constexpr int MAX_STEPS = 20;
  static constexpr float FRAME_PERIOD = 0.20f;
  static void Initialise();

  Spring(float x, float y, float z);
  void Animate(float dt);
  void ResetAnimation();
  void Render(GLint uniformModel);
private:
  static Model Spring_Model;

  void Interpolate();

  glm::vec3 _position;
  glm::vec3 _scale;
  unsigned int _frameIndex;
  unsigned int _playIndex;
  unsigned int _currStep;
  std::vector<struct SpringKeyFrame> _frameList;
  bool _isPlaying;
};
