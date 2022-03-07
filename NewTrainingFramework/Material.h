#pragma once
#include "resources.h"
#include <vector>
#include "Shader.h"
#include "Texture.h"

class Material
{
public:
	MaterialResource* materialResource;
	Shader* shader;
	std::vector<Texture*> texture;

	float kDiff;
	float sDiff;
};

