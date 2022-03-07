#include "CameraController.h"
#include "GameManager.h"
#include "Globals.h"

CameraController::CameraController (Camera* cam)
{
	camera = cam;
	camMode = CameraMode::explore;
	revertControls = -1;
	objectSelected = nullptr;
	SetCursor (LoadCursorFromFileA ("../Resources/Cursors/aero-brown-and-tan-alt.cur"));
	ShowCursor (false);

	pct.x = window::screenWidth / 2;
	pct.y = window::screenHeight / 2;
	prevPct = pct;

}
void CameraController::CameraRotation ()
{
	if (camMode == CameraMode::explore)
	{
		if (abs (deltaPos.x) > 2)
		{
			camera->rotateOy (deltaPos.x * revertControls);

		}
		if (abs (deltaPos.y) > 2)
		{
			camera->rotateOx (deltaPos.y * revertControls);

		}
		ResetCursor ();
	}
	else
	{
		if (Input::GetKey ('R'))
			camera->rotateOx (1);
		if (Input::GetKey ('T'))
			camera->rotateOx (-1);
		if (Input::GetKey ('F'))
			camera->rotateOy (1);
		if (Input::GetKey ('G'))
			camera->rotateOy (-1);
	}
}
void CameraController::RevertControls ()
{
	if (revertControls == -1)
		revertControls = 1;
	else
		revertControls = -1;
}
void CameraController::Update ()
{
	GetCursorPos (&pct);
	ScreenToClient (GameManager::getInstance ()->context->hWnd, &pct);

	deltaPos = Vector2 (pct.x - prevPct.x, pct.y - prevPct.y);
	CameraRotation ();
	CameraMovement ();
	prevPct = pct;
}
void CameraController::CameraMovement ()
{
	dir.x = 0;
	dir.y = 0;
	dir.z = 0;
	if (Input::GetKey ('S'))
	{
		dir.z = 1;
	}
	if (Input::GetKey ('W'))
	{
		dir.z = -1;
	}
	if (Input::GetKey ('A'))
	{
		dir.x = -1;
	}
	if (Input::GetKey ('D'))
	{
		dir.x = 1;
	}
	if (Input::GetKey (VK_CONTROL))
	{
		dir.y = -1;
	}
	if (Input::GetKey (VK_SPACE))
	{
		dir.y = 1;
	}
	camera->move (dir);
}

void CameraController::ResetCursor ()
{
	SetCursorPos (window::screenWidth / 2, window::screenHeight / 2);
	GetCursorPos (&pct);
	ScreenToClient (GameManager::getInstance ()->context->hWnd, &pct);
}
