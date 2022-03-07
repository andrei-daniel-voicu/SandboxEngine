#pragma once
#include "../Utilities/utilities.h"
#include "resources.h"

class Shader
{
public:
	ShaderResource* shaderResourceFS;
	ShaderResource* shaderResourceVS;
	GLuint programId, vertexShader, fragmentShader;
	GLint positionAttribute;
	GLint colorAttribute;
	GLint textureAttribute;
	GLint normAttribute;

	GLint rotationUniform;
	GLint viewUniform;
	GLint projUniform;
	GLint texUniform[5];
	GLint nrCellUniform;
	GLint heightUniform;
	GLint dispUniform;
	GLint timeUniform;

	GLint rUniform;
	GLint RUniform;
	GLint colorUniform;
	GLint cameraUniform;

	GLint selected;
	void Load ();
	~Shader ();
};