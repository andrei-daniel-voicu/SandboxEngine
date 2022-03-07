#include "SceneObject.h"
#include "SceneManager.h"
#include "Globals.h"

SceneObject::SceneObject ()
{
	changePoint = true;
	forward = Vector3 (0, 0, -1);
	angle = 0;
	trajectory = nullptr;
	position = Vector3 (0, 0, 0);
	rotation = Vector3 (0, 0, 0);
	scale = Vector3 (0.001, 0.001, 0.001);
}

void SceneObject::Start ()
{
	if (trajectory != nullptr)
	{
		if (trajectory->trajType != TrajType::circle)
			nextPosition = trajectory->GetNextPosition ();
	}
	s.SetScale (scale);
	r.SetRotationX (0);
	r.SetRotationY (0);
	r.SetRotationZ (0);
	t.SetTranslation (position);
	modelMatrix = s * r * t;
}

void SceneObject::SetScale (Vector3 newScale)
{
	scale = newScale;
	s.SetScale (scale);
	modelMatrix = s * r * t;
}

void SceneObject::SetPosition (Vector3 newPosition)
{
	position = newPosition;
	t.SetTranslation (position);
	modelMatrix = s * r * t;
}

void SceneObject::SetRotation (float angle, Vector3 newRotation)
{
	rotation = newRotation;
	r.SetRotationAngleAxis (angle, rotation);
}

void SceneObject::Draw ()
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
	if (shader->normAttribute != -1)
	{
		glEnableVertexAttribArray (shader->normAttribute);
		glVertexAttribPointer (shader->normAttribute, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*)(sizeof (Vector3) * 2));
	}
	if (shader->selected != -1)
	{
		glUniform1i (shader->selected, 1);
	}
	if (SceneManager::getInstance ()->wired == false)
	{

		glDrawElements (GL_TRIANGLES, model->nrIndices, GL_UNSIGNED_INT, &(model->indices[0]));
	}
	else
	{
		glDrawElements (GL_LINES, 2 * model->nrIndices, GL_UNSIGNED_INT, &(model->wires[0]));
		glBindBuffer (GL_ARRAY_BUFFER, 0);

		glUseProgram (SceneManager::getInstance ()->lineShader->programId);
		glBindBuffer (GL_ARRAY_BUFFER, model->normBuffer);
		if (SceneManager::getInstance ()->lineShader->positionAttribute != -1)
		{
			glEnableVertexAttribArray (SceneManager::getInstance ()->lineShader->positionAttribute);
			glVertexAttribPointer (SceneManager::getInstance ()->lineShader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof (Vector3), 0);
		}
		if (SceneManager::getInstance ()->lineShader->viewUniform != -1)
		{
			glUniformMatrix4fv (SceneManager::getInstance ()->lineShader->viewUniform, 1, GL_FALSE, (GLfloat*)SceneManager::getInstance ()->activeCamera->getViewMatrix ().m);
		}
		if (SceneManager::getInstance ()->lineShader->projUniform != -1)
		{
			glUniformMatrix4fv (SceneManager::getInstance ()->lineShader->projUniform, 1, GL_FALSE, (GLfloat*)SceneManager::getInstance ()->activeCamera->getProjMatrix ().m);

		}
		if (SceneManager::getInstance ()->lineShader->rotationUniform != -1)
		{
			glUniformMatrix4fv (SceneManager::getInstance ()->lineShader->rotationUniform, 1, GL_FALSE, (GLfloat*)modelMatrix.m);
		}
		glDrawArrays (GL_LINES, 0, 2 * model->nrVertices);
	}
	glBindBuffer (GL_ARRAY_BUFFER, 0);
}
void SceneObject::Update ()
{
	if (trajectory != nullptr)
	{
		if (trajectory->trajType != TrajType::circle)
		{
			if (changePoint == true)
			{
				forward = (nextPosition - position).Normalize ();
				trajectory->distanceToNextPoint = (nextPosition - position).Length ();
				changePoint = false;
			}
			if (trajectory->distanceTraveled >= trajectory->distanceToNextPoint)
			{
				position = nextPosition;
				t.SetTranslation (position);
				nextPosition = trajectory->GetNextPosition ();
				trajectory->distanceTraveled = 0;
				changePoint = true;
			}
			else
			{
				position += forward * speed * Time::deltaTime;
				trajectory->distanceTraveled += speed * Time::deltaTime;
				Vector3 axis = forward.Cross (Vector3 (0, 0, 1));
				float dot = forward.Dot (Vector3 (0, 0, 1));
				r.SetRotationAngleAxis (PI - acos (dot), axis.x, axis.y, axis.z);
				t.SetTranslation (position);
			}
		}
		else
		{
			Matrix rot;
			rot.SetRotationAngleAxis (90, rotAxis.x, rotAxis.y, rotAxis.z);

			t.SetTranslation (xPlane.Normalize () * radius);
			r.SetRotationAngleAxis (angle, rotAxis.x, rotAxis.y, rotAxis.z);
			angle = angle < 2 * PI ? angle + speed * Time::deltaTime / radius : angle - 2 * PI;
			modelMatrix = s * rot * t * r;
		}
	}
	if (trajectory == nullptr || trajectory->trajType != TrajType::circle)
		modelMatrix = s * r * t;
}
