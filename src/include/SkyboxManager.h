#pragma once

#include "./LightManager.h"
#include "./Skybox.h"

class SkyboxManager
{
public:
  static void Initialise();
  SkyboxManager(LightManager *lightManager);
  void DrawSkybox(glm::mat4 view, glm::mat4 projection);
private:
  static Skybox Day_Skybox;
  static Skybox Night_Skybox;

  LightManager *_lightManager;
};
