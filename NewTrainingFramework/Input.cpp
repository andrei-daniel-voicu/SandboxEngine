#include "Input.h"
#include "Globals.h"
#include <iostream>
#define VK_MSCROLL 0x07
#define SCROLL_RESET_TIME 0.2

Input* Input::instance = nullptr;
bool Input::pressed[] = { false };
bool Input::hold[] = { false };
bool Input::released[] = { false };
bool Input::input[] = { false };
float Input::timePassedScroll = 0;
int Input::wheelDir = 0;

Input* Input::getInstance ()
{
	if (!instance)
	{
		instance = new Input ();
	}
	return instance;
}

Input::Input ()
{

}

void Input::Update (ESContext* esContext, WPARAM wParam, unsigned char key, bool bIsPressed)
{
	if (!bIsPressed && input[key])
	{
		released[key] = true;
	}
	input[key] = bIsPressed;
	if (key == VK_MSCROLL)
	{
		int z = GET_WHEEL_DELTA_WPARAM (wParam);
		if (z < 0)
		{
			wheelDir = -1;
		}
		else if (z > 0)
		{
			wheelDir = 1;
		}
	}
}

void Input::ResetKeyState ()
{
	timePassedScroll += Time::deltaTime;
	for (int key = 0; key <= 255; key++)
	{
		if (input[key])
		{
			if (hold[key])
				pressed[key] = false;
			else
				pressed[key] = true;

			hold[key] = true;
			released[key] = false;
		}
		else
		{
			pressed[key] = false;
			hold[key] = false;
		}
		released[key] = false;
	}
	if (timePassedScroll >= SCROLL_RESET_TIME)
	{
		input[VK_MSCROLL] = false;
		timePassedScroll = 0;
	}
}

bool Input::GetMouseButtonDown (unsigned char key)
{
	return pressed[key];
}

bool Input::GetMouseButtonUp (unsigned char key)
{
	return released[key];
}

bool Input::GetMouseButton (unsigned char key)
{
	return hold[key];
}

bool Input::GetKeyDown (unsigned char key)
{
	return pressed[key];
}

bool Input::GetKeyUp (unsigned char key)
{
	return released[key];
}

bool Input::GetKey (unsigned char key)
{
	return hold[key];
}

int Input::GetScroll ()
{
	if (hold[VK_MSCROLL])
		return wheelDir;
	return 0;
}