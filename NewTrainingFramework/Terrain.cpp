#include "Terrain.h"
#include "SceneManager.h"

Terrain::Terrain ()
{

}

void Terrain::GenerateTerrain ()
{
	position = SceneManager::getInstance ()->activeCamera->position;

	position.y += offsetY;

	model->nrVertices = (nrCells + 1) * (nrCells + 1);
	Vertex vertex;
	for (int i = 0; i <= nrCells; i++)
	{
		for (int j = 0; j <= nrCells; j++)
		{
			vertex.pos.x = position.x + (i - nrCells / 2) * sizeCell;
			vertex.uv.x = i;
			vertex.uv.y = j;
			vertex.pos.y = position.y;
			vertex.pos.z = position.z + (j - nrCells / 2) * sizeCell;
			model->vertices.push_back (vertex);
		}

	}
	model->nrIndices = (nrCells * nrCells) * 6;
	for (unsigned int i = 0; i < model->nrVertices - nrCells - 1; i++)
	{
		if ((i + 1) % (nrCells + 1) == 0)
			continue;
		model->indices.push_back (i);
		model->indices.push_back (i + 1);
		model->indices.push_back (i + nrCells + 1);
		model->indices.push_back (i + 1);
		model->indices.push_back (i + nrCells + 2);
		model->indices.push_back (i + nrCells + 1);

	}
	for (int i = 0; i < model->nrIndices; i += 3)
	{
		model->wires.push_back (model->indices[i]);
		model->wires.push_back (model->indices[i + 1]);
		model->wires.push_back (model->indices[i + 1]);
		model->wires.push_back (model->indices[i + 2]);
		model->wires.push_back (model->indices[i + 2]);
		model->wires.push_back (model->indices[i]);
	}
	glGenBuffers (1, &(model->modelBuffer));
	glBindBuffer (GL_ARRAY_BUFFER, (model->modelBuffer));
	glBufferData (GL_ARRAY_BUFFER, sizeof (Vertex) * model->nrVertices, &(model->vertices[0]), GL_STATIC_DRAW);
	glBindBuffer (GL_ARRAY_BUFFER, 0);
}
void Terrain::Draw ()
{
	glBindBuffer (GL_ARRAY_BUFFER, model->modelBuffer);
	glUseProgram (shader->programId);

	int i = 0;
	std::vector<Texture*>::iterator ptr;
	for (ptr = texture.begin (); ptr != texture.end (); ptr++)
	{
		glActiveTexture (GL_TEXTURE0 + i);

		glBindTexture ((*ptr)->type, (*ptr)->textureBuffer);
		if (shader->texUniform[i] != -1)
			glUniform1i (shader->texUniform[i], i);

		i++;


	}
	Matrix rX, rY, rZ, t, s;
	rX.SetRotationX (rotation.x);
	rY.SetRotationY (rotation.y);
	rZ.SetRotationZ (rotation.z);

	t.SetTranslation (position);
	s.SetScale (1);

	modelMatrix = s * rX * rY * rZ * t;
	if (shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray (shader->positionAttribute);
		glVertexAttribPointer (shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), 0);
	}
	if (shader->colorAttribute != -1)
	{
		glEnableVertexAttribArray (shader->colorAttribute);
		glVertexAttribPointer (shader->colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*)sizeof (Vector3));
		// trebuie setat offset-ul
	}

	if (shader->rotationUniform != -1)
	{
		glUniformMatrix4fv (shader->rotationUniform, 1, GL_FALSE, (GLfloat*)modelMatrix.m);
	}
	if (shader->viewUniform != -1)
	{
		glUniformMatrix4fv (shader->viewUniform, 1, GL_FALSE, (GLfloat*)SceneManager::getInstance ()->activeCamera->getViewMatrix ().m);
	}
	if (shader->projUniform != -1)
	{
		glUniformMatrix4fv (shader->projUniform, 1, GL_FALSE, (GLfloat*)SceneManager::getInstance ()->activeCamera->getProjMatrix ().m);

	}
	if (shader->textureAttribute != -1)
	{
		glEnableVertexAttribArray (shader->textureAttribute);
		glVertexAttribPointer (shader->textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*)(5 * sizeof (Vector3)));
	}
	if (shader->nrCellUniform != -1)
	{
		glUniform1i (shader->nrCellUniform, nrCells);
	}
	if (shader->heightUniform != -1)
	{
		glUniform3f (shader->heightUniform, heights.x, heights.y, heights.z);
	}
	if (shader->rUniform != -1)
	{
		glUniform1f (shader->rUniform, SceneManager::getInstance ()->r);
	}
	if (shader->RUniform != -1)
	{
		glUniform1f (shader->RUniform, SceneManager::getInstance ()->R);
	}
	if (shader->colorUniform != -1)
	{
		glUniform3f (shader->colorUniform, SceneManager::getInstance ()->color.x, SceneManager::getInstance ()->color.y, SceneManager::getInstance ()->color.z);
	}
	if (shader->cameraUniform != -1)
	{
		glUniform3f (shader->cameraUniform, SceneManager::getInstance ()->activeCamera->position.x, SceneManager::getInstance ()->activeCamera->position.y, SceneManager::getInstance ()->activeCamera->position.z);
	}
	if (SceneManager::getInstance ()->wired == false)
		glDrawElements (GL_TRIANGLES, model->nrIndices, GL_UNSIGNED_INT, &(model->indices[0]));
	else
		glDrawElements (GL_LINES, 2 * model->nrIndices, GL_UNSIGNED_INT, &(model->wires[0]));
}
void Terrain::Update ()
{
	GLfloat dx = position.x - SceneManager::getInstance ()->activeCamera->position.x;
	GLfloat dz = position.z - SceneManager::getInstance ()->activeCamera->position.z;

	if (dx > sizeCell)
	{
		position.x -= sizeCell;
		for (int i = 0; i < model->nrVertices; i++)
		{
			model->vertices[i].uv.x -= 1;

		}
	}
	else if (dx < -sizeCell)
	{
		position.x += sizeCell;
		for (int i = 0; i < model->nrVertices; i++)
		{
			model->vertices[i].uv.x += 1;

		}
	}
	if (dz > sizeCell)
	{
		position.z -= sizeCell;
		for (int i = 0; i < model->nrVertices; i++)
		{
			model->vertices[i].uv.y -= 1;

		}
	}
	else if (dz < -sizeCell)
	{
		position.z += sizeCell;
		for (int i = 0; i < model->nrVertices; i++)
		{
			model->vertices[i].uv.y += 1;

		}
	}
	glBindBuffer (GL_ARRAY_BUFFER, (model->modelBuffer));
	glBufferData (GL_ARRAY_BUFFER, sizeof (Vertex) * model->nrVertices, &(model->vertices[0]), GL_STATIC_DRAW);
	glBindBuffer (GL_ARRAY_BUFFER, 0);
}