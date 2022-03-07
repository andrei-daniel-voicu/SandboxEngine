#pragma once
#include "../Utilities//Math.h"

struct Vertex 
{
	Vector3 pos;
	Vector3 col;
	Vector3 norm;
	Vector3 binorm;
	Vector3 tgt;
	Vector2 uv;
	Vertex ()
	{

	}
	Vertex (const Vertex& vert)
	{
		pos.x = vert.pos.x;
		pos.y = vert.pos.y;
		pos.z = vert.pos.z;

		norm.x = vert.norm.x;
		norm.y = vert.norm.y;
		norm.z = vert.norm.z;

		binorm.x = vert.binorm.x;
		binorm.y = vert.binorm.y;
		binorm.z = vert.binorm.z;

		tgt.x = vert.tgt.x;
		tgt.y = vert.tgt.y;
		tgt.z = vert.tgt.z;

		uv.x = vert.uv.x;
		uv.y = vert.uv.y;
	}
};