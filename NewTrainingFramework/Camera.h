#pragma once
#include "../Utilities/utilities.h"
#include "math.h"

class Camera
{	
public:
	GLfloat moveSpeed;
	GLfloat rotateSpeed;
	GLfloat camNear;
	GLfloat camFar;
	GLfloat fov;
	GLfloat deltaTime;

	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 xAxis, yAxis, zAxis;

	Matrix viewMatrix, worldMatrix,projMatrix;


	//constructors
	Camera ();

	//getters
	GLfloat getFar ();
	GLfloat getNear ();
	GLfloat getFov ();
	GLfloat getDeltaTime ();

	Matrix getViewMatrix ();
	Matrix getProjMatrix ();

	//setters
	void setDeltaTime (GLfloat);

	void moveOx (int);
	void moveOy (int);
	void moveOz (int);
	void move (Vector3 moveAxis);
	void rotateOx (int);
	void rotateOy (int);

	void updateWorldView ();

	

};

