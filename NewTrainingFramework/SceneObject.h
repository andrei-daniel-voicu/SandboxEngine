#pragma once
#include "../Utilities/utilities.h" 
#include <vector>
#include "Texture.h"
#include "Model.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"
#include <string>
#include "Trajectory.h"
class SceneObject
{
public:
	SceneObject ();
	void Start ();
	int id;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	void SetScale (Vector3);
	void SetPosition (Vector3);
	void SetRotation (float, Vector3);
public:
	Matrix modelMatrix;
	Matrix t, s, r;
	Model* model;
	std::string type;
	Shader* shader;
	Material* material;
	std::vector<Texture*> texture;
	float radius;
	Vector3 xPlane;
	Vector3 yPlane;
	Vector3 rotAxis;
	float speed;
	float angle;
	bool changePoint;
	bool selected;

	Vector3 forward;

	Trajectory* trajectory;
	Vector3 nextPosition;
	bool depthTest;
	virtual void Draw ();
	virtual void Update ();

};

