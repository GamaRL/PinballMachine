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
  SpotLight* GetObstacleLights();
private:
  // luz direccional
  DirectionalLight _mainLight;
  // Luces de tipo PoinLight
  PointLight _pointLights[MAX_POINT_LIGHTS];
  // Luces de tipo SpotLight
  SpotLight _spotLights[MAX_SPOT_LIGHTS];

  PointLight _flipperLight;
  SpotLight _obstacleLights[3];
  SpotLight _boardLight;

  bool _isFlipperLightOn;
  bool _obstacleLighstOn[3];
  bool _isBoardLightOn;
};
