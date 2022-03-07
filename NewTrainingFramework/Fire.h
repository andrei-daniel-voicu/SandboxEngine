#pragma once
#include "SceneObject.h"

class Fire : public SceneObject
{
public:
	float dispMax;
	void Draw () override;
};

