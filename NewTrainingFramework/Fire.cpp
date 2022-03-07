#include "Fire.h"
#include "SceneManager.h"
#include "Globals.h"

void Fire::Draw ()
{
	glBindBuffer (GL_ARRAY_BUFFER, model->modelBuffer);
	glUseProgram (shader->programId);

	int i = 0;
	std::vector<Texture*>::iterator ptr;
	for (ptr = texture.begin (); ptr != texture.end (); ptr++)
	{
		glActiveTexture (GL_TEXTURE0 + i);

		glBindTexture (GL_TEXTURE_2D, (*ptr)->textureBuffer);
		if (shader->texUniform[i] != -1)
			glUniform1i (shader->texUniform[i], i);

		i++;


	}
	Matrix rX, rY, rZ, t, s;
	rX.SetRotationX (rotation.x);
	rY.SetRotationY (rotation.y);

	rZ.SetRotationZ (rotation.z);
	t.SetTranslation (position);
	s.SetScale (scale);

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
	if (shader->dispUniform!=-1)
	{
		glUniform1f (shader->dispUniform, dispMax);
	}
	if (shader->timeUniform != -1)
	{
		glUniform1f (shader->timeUniform, Time::time);

	}
	glDrawElements (GL_TRIANGLES, model->nrIndices, GL_UNSIGNED_INT, &(model->indices[0]));
}
