#include "../include/LightManager.h"

#ifdef WIN32
#include <glfw3.h>
#else
#include <GLFW/glfw3.h>
#endif

LightManager::LightManager()
{
  _isFlipperLightOn = false;
  _isBoardLightOn = false;
  _obstacleLighstOn[0] = false;
  _obstacleLighstOn[1] = false;
  _obstacleLighstOn[2] = false;
  _time = 0.0f;
  _isNight = false;

  // Luz de día
	_mainLight1 = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, -1.0f, 0.0f);

  // Luz de noche
	_mainLight2 = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.05f, 0.05f,
		0.0f, -1.0f, 0.0f);

	_boardLight = SpotLight(1.0f, 1.0f, 1.0f,
		0.1f, 2.0f,
		0.0f, 100.0f, -50.0f,
		0.0f, -1.0f, 0.3f,
		0.0f, 0.0f, 0.00015f,
		30.0f);

	_obstacleLights[0] = SpotLight(1.0f, 1.0f, 0.0f,
		0.1f, 2.0f,
		50.0f, 50.0f, -50.0f,
		0.0f, -1.0f, 0.3f,
		0.0f, 0.0f, 0.0025f,
		15.0f);

	_obstacleLights[1] = SpotLight(1.0f, 1.0f, 0.0f,
		0.1f, 2.0f,
		50.0f, 50.0f, 50.0f,
		0.0f, -1.0f, 0.3f,
		0.0f, 0.0f, 0.0025f,
		15.0f);

  _obstacleLights[2] = SpotLight(1.0f, 1.0f, 0.0f,
		0.1f, 2.0f,
		-50.0f, 50.0f, 50.0f,
		0.0f, -1.0f, 0.3f,
		0.0f, 0.0f, 0.0025f,
		15.0f);

	_flipperLight = PointLight(0.0f, 1.0f, 1.0f,
		2.0f, 1.0f,
		0.0f, 5.0f, 60.0f,
		0.0f, 0.0f, 0.015f);
}


DirectionalLight* LightManager::GetAmbientLight()
{
  if (_isNight)
    return &_mainLight2;
  return &_mainLight1;
}

PointLight* LightManager::GetPointLights()
{
  _pointLights[0] = _flipperLight;
  return _pointLights;
}

SpotLight* LightManager::GetSpotLights()
{
  int i;
  for(int j = 0; j < 3; j++)
  {
    if(_obstacleLighstOn[j])
    {
      _spotLights[i] = _obstacleLights[j];
      i++;
    }
  }

  if(_isBoardLightOn)
  {
    _spotLights[i] = _boardLight;
  }

  return _spotLights;
}

unsigned int LightManager::GetNumOfPointLights()
{
  if(_isFlipperLightOn)
  {
    return 1;
  }
  return 0;
}

unsigned int LightManager::GetNumOfSpottLights()
{
  int count = 0;
  for(int j = 0; j < 3; j++)
  {
    if(_obstacleLighstOn[j])
    {
      count++;
    }
  }

  if(_isBoardLightOn)
  {
    count++;
  }

  return count;
}

void LightManager::HandleKeyBoard(bool *keys)
{

  static bool prevKeys[10];

  if (keys[GLFW_KEY_Z])
  {
    prevKeys[0] = true;
  }

  if (keys[GLFW_KEY_Z] == false && prevKeys[0])
  {
    _isFlipperLightOn = !_isFlipperLightOn;
    prevKeys[0] = false;
  }

  if (keys[GLFW_KEY_X])
  {
    prevKeys[1] = true;
  }

  if (keys[GLFW_KEY_X] == false && prevKeys[1])
  {
    _obstacleLighstOn[0] = !_obstacleLighstOn[0];
    prevKeys[1] = false;
  }

  if (keys[GLFW_KEY_C])
  {
    prevKeys[2] = true;
  }

  if (keys[GLFW_KEY_C] == false && prevKeys[2])
  {
    _obstacleLighstOn[1] = !_obstacleLighstOn[1];
    prevKeys[2] = false;
  }

  if (keys[GLFW_KEY_V])
  {
    prevKeys[3] = true;
  }

  if (keys[GLFW_KEY_V] == false && prevKeys[3])
  {
    _obstacleLighstOn[2] = !_obstacleLighstOn[2];
    prevKeys[3] = false;
  }

  if (keys[GLFW_KEY_B])
  {
    prevKeys[4] = true;
  }

  if (keys[GLFW_KEY_B] == false && prevKeys[4])
  {
    _isBoardLightOn = !_isBoardLightOn;
    prevKeys[4] = false;
  }
}

SpotLight* LightManager::GetObstacleLights()
{
  return _obstacleLights;
}

void LightManager::UpdateMainLight(float dt)
{
  _time += dt;

  if (_time >= 5.0f)
  {
    _time -= 5.0f;
    _isNight = !_isNight;
  }
}

bool LightManager::IsNight()
{
  return _isNight;
}
