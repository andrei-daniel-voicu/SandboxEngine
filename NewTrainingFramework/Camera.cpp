#include "Camera.h"

Camera::Camera ()
{
	position = Vector3 (0.f, 0.f, 0.0f);
	target = Vector3 (0.f, 0.f, 1.0f);
	up = Vector3 (0.f, 1.f, 0.f);
	zAxis = -(target - position).Normalize ();
	yAxis = up.Normalize ();
	xAxis = zAxis.Cross (yAxis).Normalize ();
	moveSpeed = 10;
	rotateSpeed = 0.3f;
	fov = 1.308;
	camNear = 0.2f;
	camFar = 10000.f;
	float scale = 1 / (tan (fov / 2));
	projMatrix.m[0][0] = scale, projMatrix.m[0][1] = 0, projMatrix.m[0][2] = 0, projMatrix.m[0][3] = 0;
	projMatrix.m[1][0] = 0, projMatrix.m[1][1] = scale, projMatrix.m[1][2] = 0, projMatrix.m[1][3] = 0;
	projMatrix.m[2][0] = 0, projMatrix.m[2][1] = 0, projMatrix.m[2][2] = -camFar / (camFar - camNear), projMatrix.m[2][3] = -1;
	projMatrix.m[3][0] = 0, projMatrix.m[3][1] = 0, projMatrix.m[3][2] = -camFar * camNear / (camFar - camNear), projMatrix.m[3][3] = 0;
	updateWorldView ();
}

GLfloat Camera::getFar ()
{
	return camFar;
}

GLfloat Camera::getNear ()
{
	return camNear;
}

GLfloat Camera::getFov ()
{
	return fov;
}

GLfloat Camera::getDeltaTime ()
{
	return deltaTime;
}
Matrix Camera::getViewMatrix ()
{
	return viewMatrix;
}
Matrix Camera::getProjMatrix ()
{
	return projMatrix;
}
void Camera::setDeltaTime (GLfloat dt)
{
	deltaTime = dt;
}
void Camera::moveOx (int dir)
{
	Vector3 move = xAxis * dir * moveSpeed * deltaTime;
	position += move;
	target += move;
	updateWorldView ();
}

void Camera::moveOy (int dir)
{
	Vector3 move = yAxis * dir * moveSpeed * deltaTime;
	position += move;
	target += move;
	updateWorldView ();

}

void Camera::moveOz (int dir)
{
	Vector3 move = zAxis * dir * moveSpeed * deltaTime;
	position += move;
	target += move;
	updateWorldView ();

}
void Camera::move (Vector3 moveAxis)
{
	if (!(moveAxis == Vector3 (0, 0, 0)))
	{
		Vector4 axis = Vector4 (moveAxis.x, moveAxis.y, moveAxis.z, 1);
		axis = axis.Normalize ();
		if (moveAxis == Vector3 (0, 1, 0) || moveAxis == Vector3 (0, -1, 0))
		{
			Vector4 move = moveAxis * moveSpeed * deltaTime;
			position += Vector3 (move.x, move.y, move.z);
			target += Vector3 (move.x, move.y, move.z);
		}
		else if (moveAxis == Vector3 (0, 0, 1))
		{
			Vector3 move = zAxis * moveSpeed * deltaTime;
			position += move;
			target += move;
		}
		else if (moveAxis == Vector3 (0, 0, -1))
		{
			Vector3 move = -zAxis * moveSpeed * deltaTime;
			position += move;
			target += move;
		}
		else if (moveAxis == Vector3 (1, 0, 0) || moveAxis == Vector3 (-1, 0, 0))
		{
			moveOx (moveAxis.x);
		}
		else
		{
			Vector4 move = worldMatrix * axis * moveSpeed * deltaTime;
			position += Vector3 (move.x, move.y, move.z);
			target += Vector3 (move.x, move.y, move.z);
		}

		updateWorldView ();
	}
}
void Camera::rotateOx (int dir)
{
	if (dir)
	{
		Matrix mRotateOX;
		mRotateOX.SetRotationX (rotateSpeed * deltaTime * dir);

		Vector4 localUp = Vector4 (0.0f, up.Length (), 0.f, 0.f);
		Vector4 rotatedLocalUp = localUp * mRotateOX;

		up = Vector3 ((rotatedLocalUp * worldMatrix).x, (rotatedLocalUp * worldMatrix).y, (rotatedLocalUp * worldMatrix).z);
		up = up.Normalize ();

		Vector4 localTarget = Vector4 (0.0f, 0.0f, -(target - position).Length (), 1);
		Vector4 rotatedTarget = localTarget * mRotateOX;
		Vector4 rot = rotatedTarget * worldMatrix;
		target = Vector3 (rot.x, rot.y, rot.z);
		updateWorldView ();
	}
}

void Camera::rotateOy (int dir)
{
	if (dir)
	{
		/*Vector4 localTarget = Vector4 (0.0f, 0.0f, -(target - position).Length (), 1);

		Matrix mRotateOY;
		mRotateOY.SetRotationY (rotateSpeed * deltaTime * dir);

		Vector4 rotatedTarget = localTarget * mRotateOY;
		Vector4 rot = rotatedTarget * worldMatrix;
		target = Vector3 (rot.x, rot.y, rot.z);*/
		Matrix rot, R;
		R.SetZero ();
		R.m[0][0] = xAxis.x; R.m[0][1] = xAxis.y; R.m[0][2] = xAxis.z;
		R.m[1][0] = yAxis.x; R.m[1][1] = yAxis.y; R.m[1][2] = yAxis.z;
		R.m[2][0] = zAxis.x; R.m[2][1] = zAxis.y; R.m[2][2] = zAxis.z;
		R.m[3][3] = 1;
		Vector4 rAxis = R * Vector4 (0, 1, 0, 0);
		rot.SetRotationAngleAxis (rotateSpeed * dir * deltaTime, rAxis.x, rAxis.y, rAxis.z);
		Vector4 localTarget = Vector4 (0.0f, 0.0f, -(target - position).Length (), 1.0f);
		Vector4 rotatedTarget = localTarget * rot;
		Vector4 target4 = rotatedTarget * worldMatrix;
		Vector4 localUp = Vector4 (0, 1, 0, 0);
		Vector4 rotatedLocalUp = localUp * rot;
		Vector4 up4 = rotatedLocalUp * worldMatrix;
		up = Vector3 (up4.x, up4.y, up4.z);
		up = up.Normalize ();
		target = Vector3 (target4.x, target4.y, target4.z);

		updateWorldView ();
	}
}
void Camera::updateWorldView ()
{
	zAxis = -(target - position).Normalize ();
	yAxis = up.Normalize ();
	xAxis = zAxis.Cross (yAxis).Normalize ();
	Matrix R, T;
	R.m[0][0] = xAxis.x, R.m[0][1] = xAxis.y, R.m[0][2] = xAxis.z, R.m[0][3] = 0;
	R.m[1][0] = yAxis.x, R.m[1][1] = yAxis.y, R.m[1][2] = yAxis.z, R.m[1][3] = 0;
	R.m[2][0] = zAxis.x, R.m[2][1] = zAxis.y, R.m[2][2] = zAxis.z, R.m[2][3] = 0;
	R.m[3][0] = 0, R.m[3][1] = 0, R.m[3][2] = 0, R.m[3][3] = 1;

	T.SetTranslation (position.x, position.y, position.z);
	worldMatrix = R * T;
	T.SetTranslation (-position.x, -position.y, -position.z);
	viewMatrix = T * R.Transpose ();
}