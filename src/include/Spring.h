#pragma once

#include "./Model.h"

#include <vector>

#ifdef WIN32
#include <glm.hpp>
#else
#include <glm/glm.hpp>
#endif

struct SpringKeyFrame
{
  //Variables para GUARDAR Key Frames
	float scale_z;		//Variable para el escalamiento
  float rot; // Variable para la rotación
	float scale_zInc;		//Variable para el incremento de la rotación
	float rot_Inc;		//Variable para el Incremento de la rotación
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
  float _rot;
  unsigned int _frameIndex;
  unsigned int _playIndex;
  unsigned int _currStep;
  std::vector<struct SpringKeyFrame> _frameList;
  bool _isPlaying;
};
