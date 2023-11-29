#pragma once

#include "./Mesh.h"
#include "./Shader.h"
#include "./CommonValues.h"

#include <vector>
#include <string>

#ifdef WIN32
#include <glew.h>
#include <glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

class Skybox
{
public:
	Skybox();
	Skybox(std::vector<std::string> faceLocations);
	void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
		
	~Skybox();
private:
	Mesh* skyMesh;
	Shader* skyShader;
	GLuint textureId;
	GLuint uniformProjection, uniformView;

};

