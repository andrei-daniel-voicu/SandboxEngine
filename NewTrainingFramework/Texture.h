#pragma once
#include "resources.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class Texture
{
public:
	Texture ();
	void Load ();
	GLuint textureBuffer;
	GLuint type;
	TextureResource* textureResource;
	~Texture ();

};

