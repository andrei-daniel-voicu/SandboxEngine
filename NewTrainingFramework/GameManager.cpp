#include "GameManager.h"
#include "Globals.h"
#include <iostream>

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance ()
{
	if (!instance)
	{
		instance = new GameManager ();
	}
	return instance;
}
void GameManager::SetContext (ESContext* esContext)
{
	context = esContext;
}
GameManager::GameManager ()
{
	camController = new CameraController (SceneManager::getInstance ()->activeCamera);
	modelID = 0;
    textureID = 0;
	selected = nullptr;
	nrModels = ResourceManager::getInstance ()->modelsRes.size ();
    nrTextures = ResourceManager::getInstance()->texturesRes.size();
}
void GameManager::Update ()
{
	if (Input::GetKeyUp ('B'))
	{
		if (camController->camMode == CameraMode::explore)
		{
			ShowCursor (true);
			selected = nullptr;
			camController->camMode = CameraMode::build;
		}
		else
		{
			ShowCursor (false);
			camController->camMode = CameraMode::explore;
		}
	}
	if (camController->camMode == CameraMode::build)
	{
		if (Input::GetKeyUp (VK_DOWN))
		{
			modelID--;
			if (modelID < 0)
			{
				modelID = nrModels - 1;
			}
			sceneObject->model = ResourceManager::getInstance ()->loadModel (modelID);
		}
		if (Input::GetKeyUp (VK_UP))
		{
			modelID++;
			if (modelID > nrModels - 1)
			{
				modelID = 0;
			}
			sceneObject->model = ResourceManager::getInstance ()->loadModel (modelID);
		}
		if (Input::GetMouseButtonUp (VK_RBUTTON) && selected == nullptr)
		{
			SpawnObject ();
			selected = sceneObject;
			camController->objectSelected = selected;
		}
		if (selected != nullptr)
		{
			ScaleObject ();
			MoveObject ();
			RotateObject ();
		}
        if (Input::GetKeyUp(VK_LEFT)) 
		{
          --textureID;
          if (textureID < 0) 
		  {
              textureID = nrTextures - 1;
		  }
          if (ResourceManager::getInstance()->loadTexture(textureID)->type ==
              GL_TEXTURE_2D)
		  {
            sceneObject->texture.size() == 0
                ? sceneObject->texture.push_back(
                      ResourceManager::getInstance()->loadTexture(textureID))
                : sceneObject->texture[0] =
                      ResourceManager::getInstance()->loadTexture(textureID);
            sceneObject->shader =
                ResourceManager::getInstance()->loadShader(0, 1);
          }

		  else {
          
		  }
        }
        if (Input::GetKeyUp(VK_RIGHT)) 
		{
          ++textureID;
          if (textureID > nrTextures - 1) 
		  {
            textureID = 0;
          }
          if (ResourceManager::getInstance()
                          ->loadTexture(textureID)
                          ->type == GL_TEXTURE_2D)
		  {
            sceneObject->texture.size() == 0
                ? sceneObject->texture.push_back(
                      ResourceManager::getInstance()->loadTexture(textureID))
                : sceneObject->texture[0] =
                      ResourceManager::getInstance()->loadTexture(textureID);
            sceneObject->shader =
                ResourceManager::getInstance()->loadShader(0, 1);
          }
        }
	}
	camController->Update ();
}

void GameManager::SpawnObject ()
{
	sceneObject = new SceneObject ();
	sceneObject->model = ResourceManager::getInstance ()->loadModel (modelID);
	sceneObject->shader = ResourceManager::getInstance ()->loadShader (12, 13);
	double x = 2.0 * (float)camController->pct.x / window::screenWidth - 1;
	double y = 2.0 * (float)camController->pct.y / window::screenHeight - 1;
	Vector4 normalizedDeviceSpace = Vector4 (x, -y, -1, 0);
	Vector4 eyeSpace = normalizedDeviceSpace * camController->camera->projMatrix.InvertMatrix ();
	eyeSpace = eyeSpace / eyeSpace.w;
	Vector4 worldSpace = eyeSpace * camController->camera->viewMatrix.InvertMatrix ();

	Vector3 cameraForward = (camController->camera->target - camController->camera->position).Normalize ();
	float dist = sceneObject->model->maxDist;
	Vector3 newPosition = Vector3 (worldSpace.x, worldSpace.y, worldSpace.z) + cameraForward * (dist / 2 * sceneObject->scale.x + 0.1);

	sceneObject->position = newPosition;
	sceneObject->Start ();
    sceneObject->SetScale(Vector3{0.05f, 0.05f, 0.05f});
	SceneManager::getInstance ()->objects.push_back (sceneObject);
}

void GameManager::MoveObject ()
{
	if (!(camController->deltaPos == Vector2 (0, 0)))
	{
		double x = 2.0 * (float)camController->pct.x / window::screenWidth - 1;
		double y = 2.0 * (float)camController->pct.y / window::screenHeight - 1;
		Vector4 normalizedDeviceSpace = Vector4 (x, -y, -1, 0);
		Vector4 eyeSpace = normalizedDeviceSpace * camController->camera->projMatrix.InvertMatrix ();
		eyeSpace = eyeSpace / eyeSpace.w;
		Vector4 worldSpace = eyeSpace * camController->camera->viewMatrix.InvertMatrix ();

		Vector3 cameraForward = (camController->camera->target - camController->camera->position).Normalize ();
		float dist = sceneObject->model->maxDist;
		Vector3 newPosition = Vector3 (worldSpace.x, worldSpace.y, worldSpace.z) + cameraForward * (dist / 2 * sceneObject->scale.x + 0.1);
		sceneObject->SetPosition (newPosition);
	}
}

void GameManager::RotateObject ()
{
}

void GameManager::ScaleObject ()
{
	if (int dir = Input::GetScroll ())
	{
		Vector3 newScale = selected->scale + Vector3 (0.3, 0.3, 0.3) * selected->scale.x * dir * Time::deltaTime
			* (selected->position - camController->camera->position).Length ();
		selected->SetScale (newScale);
	}
}
