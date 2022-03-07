#pragma once
#include <map>
#include <string>
#include <vector>
#include "SceneObject.h"
#include "xml_file.h"
#include "Camera.h"
#include "Terrain.h"
#include "Skybox.h"
#include "Fire.h"
#include "Light.h"
#include "Trajectory.h"

class SceneManager
{
private:
	static SceneManager* instance;
	SceneManager ();
public:
	static SceneManager* getInstance ();
	std::vector<SceneObject*> objects;
	void setReadDocument (const char*);
	void Init (const xml_node<>*);
	void InitialiseObject ();
	void Draw ();
	void Update (float deltaTime);
	Camera camera;
	Camera* activeCamera;

	Texture* fogTex;
	float r;
	float R;
	bool wired;
	Vector3 color;
	Shader* lineShader;
	Vector3 stof (const char*);
	enum {
		_screenSize,
		_backgroundColor,
		_controls,
		_cameras,
		_materials,
		_objects,
		_properties,
		_debug,
	}filetype;
	xml_file doc;
};

