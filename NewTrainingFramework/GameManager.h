#pragma once
#include "ResourceManager.h"
#include "SceneManager.h"
#include "CameraController.h"
#include <cmath>
#include "Input.h"

class GameManager
{
private:
	static GameManager* instance;
	GameManager ();

public:
	static GameManager* getInstance ();
	void SetContext (ESContext*);
	void Update ();
private:
	void SpawnObject ();
	void MoveObject ();
	void RotateObject ();
	void ScaleObject ();

private:
	CameraController* camController;
	int nrModels;
    int nrTextures;
	int modelID;
    int textureID;
	SceneObject* selected;
	Shader* shader;
	SceneObject* sceneObject;

public:
	ESContext* context;
};

