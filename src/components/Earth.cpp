#include "../include/Earth.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>


Model Earth::Earth_Model = Model();
Model Earth::Moon_Model = Model();
Model Earth::Base_Model = Model();

void Earth::Initialise()
{
  Earth_Model.LoadModel("resources/models/Earth.obj");
  Moon_Model.LoadModel("resources/models/Moon.obj");
  Base_Model.LoadModel("resources/models/Earth_Base.obj");
}

Earth::Earth(float x, float y, float z)
{
  _position = glm::vec3(x, y, z);
  _frameList = std::vector<struct EarthKeyFrame>(55);

  _frameList[0].rotation1 = 0.0f;
  _frameList[1].rotation1 = 60.0f;
  _frameList[2].rotation1 = 120.0f;
  _frameList[3].rotation1 = 180.0f;
  _frameList[4].rotation1 = 240.0f;
  _frameList[5].rotation1 = 300.0f;
  _frameList[6].rotation1 = 360.0f;
  _frameList[7].rotation1 = 420.0f;
  _frameList[8].rotation1 = 480.0f;
  _frameList[9].rotation1 = 540.0f;
  _frameList[10].rotation1 = 600.0f;
  _frameList[11].rotation1 = 660.0f;
  _frameList[12].rotation1 = 720.0f;
  _frameList[13].rotation1 = 780.0f;
  _frameList[14].rotation1 = 840.0f;
  _frameList[15].rotation1 = 900.0f;
  _frameList[16].rotation1 = 960.0f;
  _frameList[17].rotation1 = 1020.0f;
  _frameList[18].rotation1 = 1080.0f;
  _frameList[19].rotation1 = 1140.0f;
  _frameList[20].rotation1 = 1200.0f;
  _frameList[21].rotation1 = 1260.0f;
  _frameList[22].rotation1 = 1320.0f;
  _frameList[23].rotation1 = 1380.0f;
  _frameList[24].rotation1 = 1440.0f;
  _frameList[25].rotation1 = 1500.0f;
  _frameList[26].rotation1 = 1560.0f;
  _frameList[27].rotation1 = 1620.0f;
  _frameList[28].rotation1 = 1680.0f;
  _frameList[29].rotation1 = 1740.0f;
  _frameList[30].rotation1 = 1800.0f;
  _frameList[31].rotation1 = 1860.0f;
  _frameList[32].rotation1 = 1920.0f;
  _frameList[33].rotation1 = 1980.0f;
  _frameList[34].rotation1 = 2040.0f;
  _frameList[35].rotation1 = 2100.0f;
  _frameList[36].rotation1 = 2160.0f;
  _frameList[37].rotation1 = 2220.0f;
  _frameList[38].rotation1 = 2280.0f;
  _frameList[39].rotation1 = 2340.0f;
  _frameList[40].rotation1 = 2400.0f;
  _frameList[41].rotation1 = 2460.0f;
  _frameList[42].rotation1 = 2520.0f;
  _frameList[43].rotation1 = 2580.0f;
  _frameList[44].rotation1 = 2640.0f;
  _frameList[45].rotation1 = 2700.0f;
  _frameList[46].rotation1 = 2760.0f;
  _frameList[47].rotation1 = 2820.0f;
  _frameList[48].rotation1 = 2880.0f;
  _frameList[49].rotation1 = 2940.0f;
  _frameList[50].rotation1 = 3000.0f;
  _frameList[51].rotation1 = 3060.0f;
  _frameList[52].rotation1 = 3120.0f;
  _frameList[53].rotation1 = 3180.0f;
  _frameList[54].rotation1 = 3240.0f;

_frameList[0].rotation2 = 0;
_frameList[1].rotation2 = 360;
_frameList[2].rotation2 = 720;
_frameList[3].rotation2 = 1080;
_frameList[4].rotation2 = 1440;
_frameList[5].rotation2 = 1800;
_frameList[6].rotation2 = 2160;
_frameList[7].rotation2 = 2520;
_frameList[8].rotation2 = 2880;
_frameList[9].rotation2 = 3240;
_frameList[10].rotation2 = 3600;
_frameList[11].rotation2 = 3960;
_frameList[12].rotation2 = 4320;
_frameList[13].rotation2 = 4680;
_frameList[14].rotation2 = 5040;
_frameList[15].rotation2 = 5400;
_frameList[16].rotation2 = 5760;
_frameList[17].rotation2 = 6120;
_frameList[18].rotation2 = 6480;
_frameList[19].rotation2 = 6840;
_frameList[20].rotation2 = 7200;
_frameList[21].rotation2 = 7560;
_frameList[22].rotation2 = 7920;
_frameList[23].rotation2 = 8280;
_frameList[24].rotation2 = 8640;
_frameList[25].rotation2 = 9000;
_frameList[26].rotation2 = 9360;
_frameList[27].rotation2 = 9720;
_frameList[28].rotation2 = 10080;
_frameList[29].rotation2 = 10440;
_frameList[30].rotation2 = 10800;
_frameList[31].rotation2 = 11160;
_frameList[32].rotation2 = 11520;
_frameList[33].rotation2 = 11880;
_frameList[34].rotation2 = 12240;
_frameList[35].rotation2 = 12600;
_frameList[36].rotation2 = 12960;
_frameList[37].rotation2 = 13320;
_frameList[38].rotation2 = 13680;
_frameList[39].rotation2 = 14040;
_frameList[40].rotation2 = 14400;
_frameList[41].rotation2 = 14760;
_frameList[42].rotation2 = 15120;
_frameList[43].rotation2 = 15480;
_frameList[44].rotation2 = 15840;
_frameList[45].rotation2 = 16200;
_frameList[46].rotation2 = 16560;
_frameList[47].rotation2 = 16920;
_frameList[48].rotation2 = 17280;
_frameList[49].rotation2 = 17640;
_frameList[50].rotation2 = 18000;
_frameList[51].rotation2 = 18360;
_frameList[52].rotation2 = 18720;
_frameList[53].rotation2 = 19080;
_frameList[54].rotation2 = 19440;


  ResetAnimation();
}

void Earth::ResetAnimation()
{
  _playIndex = 0;
  _rotation1 = _frameList[0].rotation1;
  _rotation2 = _frameList[0].rotation2;
  _isPlaying = true;
  _currStep = 0;
  _accumulatedTime = 0.0f;
}

void Earth::Interpolate()
{
  _frameList[_playIndex].rotation1_Inc = (_frameList[_playIndex + 1].rotation1 - _frameList[_playIndex].rotation1) / MAX_STEPS;
  _frameList[_playIndex].rotation2_Inc = (_frameList[_playIndex + 1].rotation2 - _frameList[_playIndex].rotation2) / MAX_STEPS;
}

void Earth::Animate(float dt)
{
  float time = _accumulatedTime + dt;
  while (_isPlaying && time >= FRAME_PERIOD / MAX_STEPS)
  {
    if (_currStep >= MAX_STEPS) // fin de animación entre frames?
    {
      _playIndex++;
      if (_playIndex > _frameList.size() - 2) // Fin de toda la animación con último frame?
      {
        _playIndex = 0;
        _isPlaying = false;
      }
      else // Interpolación del próximo cuadro
      {
        _rotation1 = _frameList[_playIndex].rotation1;
        _rotation2 = _frameList[_playIndex].rotation2;
        _currStep = 0; // Resetea contador
        // Interpolar
        Interpolate();
      }
    }
    else
    {
      // Dibujar Animación
      _rotation1 += _frameList[_playIndex].rotation1_Inc;
      _rotation2 += _frameList[_playIndex].rotation2_Inc;
      _currStep++;
    }
    time -= FRAME_PERIOD / MAX_STEPS;
  }

  _accumulatedTime = time;
}

void Earth::Render(GLint uniformModel)
{
  glm::mat4 model, modelaux;

  const float radians1 = glm::radians(_rotation1);
  const float radians2 = glm::radians(_rotation1);

  model = glm::mat4(1.0);
  model = glm::translate(model, _position);
  model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
  modelaux = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Base_Model.RenderModel();

  model = modelaux;
  model = glm::translate(model, glm::vec3(0.0f, 4.0f, 0.0f));
  modelaux = model;
  model = glm::rotate(model, radians2, glm::vec3(0, 1, 0));
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Earth_Model.RenderModel();

  model = modelaux;
  model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1, 0, 0));
  model = glm::translate(model, 5.0f * glm::vec3(glm::cos(radians1), 0.0f, glm::sin(radians1)));
  modelaux = model;
  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  Moon_Model.RenderModel();
}
