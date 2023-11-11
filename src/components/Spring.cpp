#include "../include/Spring.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>


Model Spring::Spring_Model = Model();

void Spring::Initialise()
{
  Spring_Model.LoadModel("resources/models/Spring.obj");
}

Spring::Spring(float x, float y, float z)
{
  _position = glm::vec3(x, y, z);
  _frameList = std::vector<struct SpringKeyFrame>(8);

  _frameList[0].scale_z = -0.30f;
  _frameList[0].rot = 120.0f;
  _frameList[1].scale_z = -0.50f;
  _frameList[1].rot = 240.0f;
  _frameList[2].scale_z = -0.70f;
  _frameList[2].rot = 360.0f;
  _frameList[3].scale_z = 0.00f;
  _frameList[3].rot = 360.0f;
  _frameList[4].scale_z = -0.20f;
  _frameList[4].rot = 360.0f;
  _frameList[5].scale_z = 0.00f;
  _frameList[5].rot = 360.0f;
  _frameList[6].scale_z = -0.20f;
  _frameList[6].rot = 360.0f;
  _frameList[7].scale_z = -0.10f;
  _frameList[7].rot = 360.0f;
}

void Spring::ResetAnimation()
{
  _playIndex = 0;
  _scale = glm::vec3(1.0f, 1.0f, _frameList[0].scale_z);
  _rot = _frameList[0].rot;
  _isPlaying = true;
  _currStep = 0;
}

void Spring::Interpolate()
{
	_frameList[_playIndex].scale_zInc = (_frameList[_playIndex + 1].scale_z - _frameList[_playIndex].scale_z) / MAX_STEPS;
	_frameList[_playIndex].rot_Inc = (_frameList[_playIndex + 1].rot - _frameList[_playIndex].rot) / MAX_STEPS;
}

void Spring::Animate(float dt)
{
  float time = 0.0f;
  while(_isPlaying && time < dt)
  {
    if (_currStep >= MAX_STEPS) //fin de animación entre frames?
    {
      _playIndex++;
      if (_playIndex > _frameList.size() - 2)	//Fin de toda la animación con último frame?
      {
        _playIndex = 0;
        _isPlaying = false;
      }
      else //Interpolación del próximo cuadro
      {
        _scale.z = _frameList[_playIndex].scale_z;
        _rot = _frameList[_playIndex].rot;
        _currStep = 0; //Resetea contador
        //Interpolar
        Interpolate();
      }
    }
    else
    {
      //Dibujar Animación
      _scale.z += _frameList[_playIndex].scale_zInc;
      _rot = _frameList[_playIndex].rot_Inc;
      _currStep++;
    }
    time += FRAME_PERIOD / MAX_STEPS;
  }
}

void Spring::Render(GLint uniformModel)
{
  glm::mat4 model;

  model = glm::mat4(1.0);
  model = glm::translate(model, _position);
  model = glm::scale(model, _scale + 1.0f);
  model = glm::rotate(model, glm::radians(_rot), glm::vec3(0, 0, 1));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Spring_Model.RenderModel();
}
