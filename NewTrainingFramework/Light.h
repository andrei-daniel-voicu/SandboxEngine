#pragma once
#include "../Utilities/utilities.h" 

class Light
{
	enum lightType
	{
		point,
		directional,
		spotlight,
	}type;
	Vector3 position;
	Vector3 diffuseColor;
	Vector3 specularColor;

};

