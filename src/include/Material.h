#pragma once

#ifdef WIN32
#include <glew.h>
#else
#include <GL/glew.h>
#endif

//Esta clase está pensada para crear materiales asignables a nuestros diferentes objetos y luces
class Material
{
public:
	Material();
	Material(GLfloat sIntensity, GLfloat shine);

	void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

	~Material();

private: 
	GLfloat specularIntensity;
	GLfloat shininess;
};

