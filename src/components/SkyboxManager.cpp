#include "../include/SkyboxManager.h"
#include <string>

Skybox SkyboxManager::Day_Skybox;
Skybox SkyboxManager::Night_Skybox;

void SkyboxManager::Initialise()
{
  std::vector<std::string> nightFaces = std::vector<std::string>();
	nightFaces.push_back("resources/textures/skybox/night_rt.png");
	nightFaces.push_back("resources/textures/skybox/night_lf.png");
	nightFaces.push_back("resources/textures/skybox/night_dn.png");
	nightFaces.push_back("resources/textures/skybox/night_up.png");
	nightFaces.push_back("resources/textures/skybox/night_bk.png");
	nightFaces.push_back("resources/textures/skybox/night_ft.png");

  SkyboxManager::Night_Skybox = Skybox(nightFaces);

	std::vector<std::string> dayFaces;
	dayFaces.push_back("resources/textures/skybox/day_rt.png");
	dayFaces.push_back("resources/textures/skybox/day_lf.png");
	dayFaces.push_back("resources/textures/skybox/day_dn.png");
	dayFaces.push_back("resources/textures/skybox/day_up.png");
	dayFaces.push_back("resources/textures/skybox/day_bk.png");
	dayFaces.push_back("resources/textures/skybox/day_ft.png");

  SkyboxManager::Day_Skybox = Skybox(dayFaces);

}

SkyboxManager::SkyboxManager(LightManager *lightManager)
{
  _lightManager = lightManager;
}

void SkyboxManager::DrawSkybox(glm::mat4 view, glm::mat4 projection)
{
  if(_lightManager->IsNight())
    SkyboxManager::Night_Skybox.DrawSkybox(view, projection);
  else
    SkyboxManager::Day_Skybox.DrawSkybox(view, projection);
}

