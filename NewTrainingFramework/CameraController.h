#pragma once
#include "Camera.h"
#include <Windows.h>
#include "SceneObject.h"

enum class CameraMode
{
	build,
	explore,
};

class CameraController
{
public:
	CameraController (Camera*);

	void RevertControls ();
	void Update ();

private:
	void CameraRotation ();
	void CameraMovement ();
	void ResetCursor ();

public:
	CameraMode camMode;
	Camera* camera;
	Vector2 deltaPos;
	SceneObject* objectSelected;
	Vector3 dir;
	POINT pct;
	POINT prevPct;
private:
	int revertControls;
};

