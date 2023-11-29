#pragma once

#include "./DirectionalLight.h"
#include "./PointLight.h"
#include "./SpotLight.h"
#include "./CommonValues.h"

class LightManager
{
public:
  LightManager();
  DirectionalLight* GetAmbientLight();
  PointLight* GetPointLights();
  SpotLight* GetSpotLights();
  unsigned int GetNumOfPointLights();
  unsigned int GetNumOfSpottLights();
  void HandleKeyBoard(bool* keys);
  void UpdateMainLight(float dt);
  SpotLight* GetObstacleLights();
  bool IsNight();
private:
  // Luces direccionales
  DirectionalLight _mainLight1;
  DirectionalLight _mainLight2;

  // Arreglo de luces de tipo PoinLight
  PointLight _pointLights[MAX_POINT_LIGHTS];

  // Arreglo de luces de tipo SpotLight
  SpotLight _spotLights[MAX_SPOT_LIGHTS];

  PointLight _flipperLight;
  SpotLight _obstacleLights[3];
  SpotLight _boardLight;

  bool _isFlipperLightOn;
  bool _obstacleLighstOn[3];
  bool _isBoardLightOn;
  bool _isNight;

  float _time;
};
