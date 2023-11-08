#pragma once

#ifdef WIN32
#include <glew.h>
#else
#include <GL/glew.h>
#endif

class Texture
{
public:
	Texture();
	Texture(const char* FileLoc);
	bool LoadTexture();
	bool LoadTextureA();
	void UseTexture();
	void ClearTexture();
	~Texture();
private: 
	GLuint textureID;
	int width, height, bitDepth;
	const char *fileLocation;

};

