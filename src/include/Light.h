#pragma once

#ifdef WIN32
#include <glew.h>
#include <glm.hpp>
#else
#include <GL/glew.h>
#include <glm/glm.hpp>
#endif

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, 
			GLfloat aIntensity, GLfloat dIntensity);

	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

