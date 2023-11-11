#include "../include/Spring.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>


Model Spring::Spring_Model = Model();

void Spring::Initialise()
{
  Spring_Model.LoadModel("resources/models/Spring.obj");
}

Spring::Spring(float x, float y, float z)
{
  _position = glm::vec3(x, y, z);
  _frameList = std::vector<struct SpringKeyFrame>(12);
  _frameList[0].scaleBall_z = 0.100000f;
  _frameList[1].scaleBall_z = 3.000000f;
  _frameList[2].scaleBall_z = 0.100000f;
  _frameList[3].scaleBall_z = 3.000000f;
  _frameList[4].scaleBall_z = 0.100000f;
  _frameList[5].scaleBall_z = 3.000000f;
  _frameList[6].scaleBall_z = 0.100000f;
  _frameList[7].scaleBall_z = 3.000000f;
  _frameList[8].scaleBall_z = 0.100000f;
  _frameList[9].scaleBall_z = 3.000000f;
  _frameList[10].scaleBall_z = 0.200000f;
  _frameList[11].scaleBall_z = 1.00000f;
}

void Spring::ResetAnimation()
{
  _playIndex = 0;
  _scale = glm::vec3(1.0f, 1.0f, 1.0f);
  _isPlaying = true;
  _currStep = 0;
}

void Spring::Interpolate()
{
	_frameList[_playIndex].scaleBall_zInc = (_frameList[_playIndex + 1].scaleBall_z - _frameList[_playIndex].scaleBall_z) / MAX_STEPS;
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
        _scale.z = _frameList[_playIndex].scaleBall_z;
        _currStep = 0; //Resetea contador
        //Interpolar
        Interpolate();
      }
    }
    else
    {
      //Dibujar Animación
      _scale.z += _frameList[_playIndex].scaleBall_zInc;
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
  model = glm::scale(model, _scale);
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Spring_Model.RenderModel();
}
