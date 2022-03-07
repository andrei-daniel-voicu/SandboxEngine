#pragma once
#include "SceneObject.h"
class Terrain : public SceneObject
{
public:

	int nrCells;
	float sizeCell;
	float offsetY;
	Vector3 heights;
	Terrain ();
	void GenerateTerrain ();
	void Draw () override;
	void Update () override;
};

