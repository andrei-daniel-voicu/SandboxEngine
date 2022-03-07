#include "Model.h"


Model::Model ()
{
	maxDist = 0;
}
void Model::Load ()
{
	char sir[100];
	std::ifstream in (modelResource->path);
	in.getline (sir, 100, ' ');
	in >> nrVertices;
	GLfloat pos, norm, binorm, tgt, uv;
	Vertex vertex;
	unsigned int indice;
	char dummy;
	for (int i = 0; i < nrVertices; i++)
	{
		in.getline (sir, 100, '[');
		in >> pos;
		vertex.pos.x = pos;
		in.get ();
		in.get ();
		in >> pos;
		vertex.pos.y = pos;
		in.get ();
		in.get ();
		in >> pos;
		vertex.pos.z = pos;

		in.getline (sir, 100, '[');
		in >> norm;
		vertex.norm.x = norm;
		in.get ();
		in.get ();
		in >> norm;
		vertex.norm.y = norm;
		in.get ();
		in.get ();
		in >> norm;
		vertex.norm.z = norm;

		in.getline (sir, 100, '[');
		in >> binorm;
		vertex.binorm.x = binorm;
		in.get ();
		in.get ();
		in >> binorm;
		vertex.binorm.y = binorm;
		in.get ();
		in.get ();
		in >> binorm;
		vertex.binorm.z = binorm;

		in.getline (sir, 100, '[');
		in >> tgt;
		vertex.tgt.x = tgt;
		in.get ();
		in.get ();
		in >> tgt;
		vertex.tgt.y = tgt;
		in.get ();
		in.get ();
		in >> tgt;
		vertex.tgt.z = tgt;

		in.getline (sir, 100, '[');
		in >> uv;
		vertex.uv.x = uv;
		in.get ();
		in.get ();
		in >> uv;
		vertex.uv.y = uv;
		vertices.push_back (vertex);

	}
	in.getline (sir, 100, ' ');
	in >> nrIndices;
	for (int i = 0; i < nrIndices / 3; i++)
	{
		in.getline (sir, 100, '.');
		in.getline (sir, 100, ' ');
		in >> indice;
		indices.push_back (indice);


		in.getline (sir, 100, ' ');
		in >> indice;
		indices.push_back (indice);

		in.getline (sir, 100, ' ');
		in >> indice;
		indices.push_back (indice);
	}
	for (int i = 0; i < nrIndices; i += 3)
	{
		wires.push_back (indices[i]);
		wires.push_back (indices[i + 1]);
		wires.push_back (indices[i + 1]);
		wires.push_back (indices[i + 2]);
		wires.push_back (indices[i + 2]);
		wires.push_back (indices[i]);
	}
	for (int i = 0; i < nrVertices; i++)
	{
		lines.push_back (vertices[i].pos);
		lines.push_back (vertices[i].pos + vertices[i].norm * 50);
	}
	for (int i = 0; i < nrVertices; i++)
		for (int j = i + 1; j < nrVertices; j++)
			if ((vertices[i].pos - vertices[j].pos).Length () > maxDist)
			{
				maxDist = (vertices[i].pos - vertices[j].pos).Length ();
			}
	glGenBuffers (1, &modelBuffer);
	glBindBuffer (GL_ARRAY_BUFFER, modelBuffer);
	glBufferData (GL_ARRAY_BUFFER, sizeof (Vertex) * nrVertices, &(vertices[0]), GL_STATIC_DRAW);
	glBindBuffer (GL_ARRAY_BUFFER, 0);

	glGenBuffers (1, &normBuffer);
	glBindBuffer (GL_ARRAY_BUFFER, normBuffer);
	glBufferData (GL_ARRAY_BUFFER, sizeof (Vector3) * nrVertices * 2, &(lines[0]), GL_STATIC_DRAW);
	glBindBuffer (GL_ARRAY_BUFFER, 0);
}
Model::~Model ()
{

}