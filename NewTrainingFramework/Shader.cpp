#include "Shader.h"
#include <iostream>
void Shader::Load ()
{
	vertexShader = esLoadShader (GL_VERTEX_SHADER, shaderResourceVS->path);

	if (vertexShader == 0)
	{
		exit (-1);
	}

	fragmentShader = esLoadShader (GL_FRAGMENT_SHADER, shaderResourceFS->path);

	if (fragmentShader == 0)
	{
		glDeleteShader (vertexShader);
		exit (-1);


	}

	programId = esLoadProgram (vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation (programId, "a_posL");
	colorAttribute = glGetAttribLocation (programId, "a_color");
	textureAttribute = glGetAttribLocation (programId, "a_uv");
	normAttribute = glGetAttribLocation (programId, "a_norm");

	rotationUniform = glGetUniformLocation (programId, "u_rotation");
	viewUniform = glGetUniformLocation (programId, "u_view");
	projUniform = glGetUniformLocation (programId, "u_proj");
	texUniform[0] = glGetUniformLocation (programId, "u_texture_0");
	texUniform[1] = glGetUniformLocation (programId, "u_texture_1");

	texUniform[2] = glGetUniformLocation (programId, "u_texture_2");
	texUniform[3] = glGetUniformLocation (programId, "u_texture_3");

	texUniform[4] = glGetUniformLocation (programId, "u_texture_4");
	nrCellUniform = glGetUniformLocation (programId, "u_nrCells");
	heightUniform = glGetUniformLocation (programId, "u_height");

	colorUniform = glGetUniformLocation (programId, "u_color");
	rUniform = glGetUniformLocation (programId, "u_r");
	RUniform = glGetUniformLocation (programId, "u_R");
	cameraUniform = glGetUniformLocation (programId, "u_cameraPos");

	dispUniform = glGetUniformLocation (programId, "u_dispMax");
	timeUniform = glGetUniformLocation (programId, "u_time");

	selected = glGetUniformLocation (programId, "u_selected");
}

Shader::~Shader ()
{
	glDeleteProgram (programId);
	glDeleteShader (vertexShader);
	glDeleteShader (fragmentShader);
}