#include "SceneManager.h"
#include "ResourceManager.h"
#include "xml_file.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::getInstance ()
{
	if (!instance)
	{
		instance = new SceneManager ();
	}
	return instance;
}
SceneManager::SceneManager ()
{
	wired = false;
}
void SceneManager::setReadDocument (const char* path)
{
	doc.xmlLoad (path);

}
void SceneManager::Init (const xml_node<>* node)
{
	xml_attribute<>* pAttr;
	std::string sir;
	std::string value;
	for (pAttr = node->first_attribute (); pAttr; pAttr = pAttr->next_attribute ())
	{
		sir = pAttr->name ();
		value = pAttr->value ();
		switch (filetype)
		{
		case _objects:
			if (sir == "type")
			{
				if (value == "normal" || value == "reflected")
					objects.push_back (new SceneObject ());
				else if (value == "terrain")
					objects.push_back (new Terrain);
				else if (value == "skybox")
					objects.push_back (new Skybox);
				else if (value == "fire")
					objects.push_back (new Fire);
				objects.back ()->type = pAttr->value ();

			}
			else if (sir == "id")
			{

				objects.back ()->id = std::stoi (pAttr->value ());
			}


			else if (sir == "scale")
			{
				objects.back ()->scale = stof (pAttr->value ());
				objects.back ()->s.SetScale (objects.back ()->scale);

			}
			else if (sir == "rotation")
			{
				objects.back ()->rotation = stof (pAttr->value ());
				Vector3 axis = objects.back ()->forward.Cross (Vector3 (0, 0, 1));
				float dot = objects.back ()->forward.Dot (Vector3 (0, 0, 1));
				objects.back ()->r.SetRotationAngleAxis (PI - acos (dot), axis.x, axis.y, axis.z);

			}
			else if (sir == "position")
			{
				objects.back ()->position = stof (pAttr->value ());
				objects.back ()->t.SetTranslation (objects.back ()->position);

			}
			else if (sir == "modelId")
			{

				if (objects.back ()->type == "normal" || objects.back ()->type == "skybox" || objects.back ()->type == "fire" || objects.back ()->type == "reflected")
				{

					objects.back ()->model = ResourceManager::getInstance ()->loadModel (std::stoi (pAttr->value ()));
				}
				else if (objects.back ()->type == "terrain")
				{
					ResourceManager::getInstance ()->models.push_back (new Model ());
					objects.back ()->model = ResourceManager::getInstance ()->models.back ();
				}
			}
			else if (sir == "nrCells")
			{
				((Terrain*)(objects.back ()))->nrCells = std::stoi (pAttr->value ());
			}
			else if (sir == "sizeCell")
			{
				((Terrain*)(objects.back ()))->sizeCell = std::stof (pAttr->value ());


			}
			else if (sir == "offsetY")
			{
				((Terrain*)(objects.back ()))->offsetY = std::stof (pAttr->value ());

			}
			else if (sir == "height")
			{
				((Terrain*)(objects.back ()))->heights = stof (pAttr->value ());
			}
			else if (sir == "dispMax")
			{
				((Fire*)(objects.back ()))->dispMax = std::stof (pAttr->value ());
			}
			else if (sir == "textureId")
			{
				char* str = pAttr->value ();
				int nr = 0;
				for (int i = 0; str[i]; i++)
				{
					if (str[i] == ' ')
					{

						objects.back ()->texture.push_back (ResourceManager::getInstance ()->loadTexture (nr));
						nr = 0;
					}
					else nr = nr * 10 + str[i] - '0';
				}
				objects.back ()->texture.push_back (ResourceManager::getInstance ()->loadTexture (nr));
				if (objects.back ()->type == "terrain" || objects.back ()->type == "normal" || objects.back ()->type == "reflected")
					objects.back ()->texture.push_back (fogTex);

			}
			else if (sir == "shaderId")
			{
				objects.back ()->shader = ResourceManager::getInstance ()->loadShader (std::stoi (pAttr->value ()), std::stoi (pAttr->value ()) + 1);
			}
			else if (sir == "trajectoryType")
			{
				objects.back ()->trajectory = new Trajectory ();
				if (value == "linear")
				{
					objects.back ()->trajectory->trajType = TrajType::linear;
				}
				else
				{
					objects.back ()->trajectory->trajType = TrajType::circle;
				}
			}
			else if (sir == "iteration")
			{
				if (value == "infinite")
				{
					objects.back ()->trajectory->iteration = -1;
				}
				else
				{
					objects.back ()->trajectory->iteration = std::stoi (value);
				}
			}
			else if (sir == "direction")
			{
				if (value == "normal")
				{
					objects.back ()->trajectory->trajDir = TrajDir::normal;
				}
				else
				{
					objects.back ()->trajectory->trajDir = TrajDir::alternate;
				}
			}
			else if (sir == "points")
			{
				for (int i = 0; pAttr->value ()[i]; i++)
				{
					if (i == 0)
					{
						objects.back ()->trajectory->trajPoints.push_back (stof (pAttr->value ()));
					}
					else if (pAttr->value ()[i] == ';')
					{
						objects.back ()->trajectory->trajPoints.push_back (stof (pAttr->value () + i + 1));
					}
				}
			}
			else if (sir == "radius")
			{
				objects.back ()->radius = std::stof (value);
			}
			else if (sir == "rotationPlane")
			{
				for (int i = 0; pAttr->value ()[i]; i++)
				{
					if (i == 0)
					{
						objects.back ()->xPlane = stof (pAttr->value () + i);
					}
					else if (pAttr->value ()[i] == ';')
					{
						objects.back ()->yPlane = stof (pAttr->value () + i + 1);
					}
				}
				objects.back ()->rotAxis = objects.back ()->xPlane.Cross (objects.back ()->yPlane);
			}
			else if (sir == "speed")
			{
				objects.back ()->speed = std::stof (value);
			}
			break;
		case _cameras:
			if (sir == "id")
			{
				activeCamera = &camera;
			}
			else if (sir == "position")
			{
				//camera->position = stof (pAttr->value ());
			}
			else if (sir == "target")
			{
				//camera->target = stof (pAttr->value ());
			}
			else if (sir == "translationSpeed")
			{
				//camera->moveSpeed = std::stof (pAttr->value ());
			}
			else if (sir == "rotationSpeed")
			{
				//camera->rotateSpeed = std::stof (pAttr->value ());
			}
			else if (sir == "fov")
			{
				//camera->fov = std::stof (pAttr->value ());
			}
			else if (sir == "near")
			{
				//camera->camNear = std::stof (pAttr->value ());
			}
			else if (sir == "far")
			{
				//camera->camFar = std::stof (pAttr->value ());
			}
			break;
		case _properties:
			if (sir == "r")
			{
				r = std::stoi (pAttr->value ());
			}
			else if (sir == "R")
			{
				R = std::stoi (pAttr->value ());
			}
			else if (sir == "textureId")
			{

				char* str = pAttr->value ();
				int nr = 0;
				for (int i = 0; str[i]; i++)
				{
					if (str[i] == ' ')
					{
						fogTex = ResourceManager::getInstance ()->loadTexture (nr);

						nr = 0;
					}
					else nr = nr * 10 + str[i] - '0';
				}
				fogTex = ResourceManager::getInstance ()->loadTexture (nr);


			}
			break;
		case _debug:
			if (sir == "id")
			{
				lineShader = ResourceManager::getInstance ()->loadShader (std::stoi (pAttr->value ()), std::stoi (pAttr->value ()) + 1);
			}
			break;
		}
	}
	for (xml_node<>* n = node->first_node (); n; n = n->next_sibling ())
	{
		std::string value = n->name ();
		if (value == "objects")
		{
			filetype = _objects;
		}
		else if (value == "cameras")
		{
			filetype = _cameras;
		}
		else if (value == "properties")
		{
			filetype = _properties;
		}
		else if (value == "debugSettings")
		{
			filetype = _debug;
		}
		Init (n);


	}
}

Vector3 SceneManager::stof (const char* string)
{
	Vector3 vector = Vector3 (0, 0, 0);
	sscanf (string, "%f %f %f", &vector.x, &vector.y, &vector.z);
	return vector;
}
void SceneManager::InitialiseObject ()
{
	std::vector<SceneObject*>::iterator ptr;
	for (ptr = objects.begin (); ptr != objects.end (); ptr++)
	{
		if ((*ptr)->type == "terrain")
		{
			((Terrain*)(*ptr))->GenerateTerrain ();
		}
		else
		{
			(*ptr)->Start ();
		}
	}

	for (ptr = objects.begin (); ptr != objects.end (); ptr++)
		if ((*ptr)->type == "fire") break;
	//std::rotate (ptr, ptr + 1, objects.end ());
	for (ptr = objects.begin (); ptr != objects.end (); ptr++)
		if ((*ptr)->type == "skybox") break;
	std::vector<SceneObject*>::iterator ptr1;
	for (ptr1 = objects.begin (); ptr1 != objects.end (); ptr1++)
		if ((*ptr1)->type == "reflected")
		{
			(*ptr1)->texture.push_back ((*ptr)->texture.back ());
		}

}

void SceneManager::Draw ()
{
	int r = glGetError ();

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	std::vector<SceneObject*>::iterator ptr;
	GLint i = 0;
	for (ptr = objects.begin (); ptr != objects.end (); ptr++, i++)
	{
		glStencilFunc (GL_ALWAYS, i, 0xff);
		(*ptr)->Draw ();
	}

	unsigned char nr = 0;
	GLboolean verif = 0;
	float x;
	glPixelStorei (GL_PACK_ALIGNMENT, 4);

	glReadPixels (0, 0, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &x);
	r = glGetError ();
	glBindFramebuffer (GL_FRAMEBUFFER, 0);
}

void SceneManager::Update (float deltaTime)
{
	std::vector<SceneObject*>::iterator ptr;
	for (ptr = objects.begin (); ptr != objects.end (); ptr++)
	{

		(*ptr)->Update ();
	}
}
