#pragma once
#include "../Utilities/utilities.h"

class Input
{
private:
	static Input* instance;
	Input ();

public:
	static Input* getInstance ();
	static void Update (ESContext*, WPARAM, unsigned char, bool);
	static void ResetKeyState ();
	static bool GetMouseButtonDown (unsigned char);
	static bool GetMouseButtonUp (unsigned char);
	static bool GetMouseButton (unsigned char);
	static int GetScroll ();
	static bool GetKeyDown (unsigned char);
	static bool GetKeyUp (unsigned char);
	static bool GetKey (unsigned char);
private:
	static bool input[256];
	static bool pressed[256];
	static bool released[256];
	static bool hold[256];
	static float timePassedScroll;
	static int wheelDir;
};

