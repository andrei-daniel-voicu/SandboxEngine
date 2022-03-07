#pragma once
#include "Vertex.h"
#include "resources.h"
#include <vector>
#include <fstream>
#include <iostream>

class Model
{
public:
	GLuint modelBuffer;
	GLuint normBuffer;
	int nrVertices,nrIndices;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> wires;
	std::vector<Vector3> lines;
	float maxDist;
	//constructors
	Model ();
	~Model ();

	void Load ();
	ModelResource* modelResource;
};

