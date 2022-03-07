#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "xml_file.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Globals.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "Input.h"

float _time = 1;

GLuint frameBuffer;
GLuint depthRenderBuffer;
GLuint texture;

int Init (ESContext* esContext)
{
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable (GL_STENCIL_TEST);
	glStencilMask (0xff);
	glClearStencil (0);
	glStencilOp (GL_KEEP, GL_KEEP, GL_REPLACE);

	//glGetIntegerv (GL_STENCIL_CLEAR_VALUE
	//	, &ta);

	glEnable (GL_DEPTH_TEST);
	/*GLint texWidth = window::screenWidth;
	GLint texHeight = window::screenHeight;
	glGenFramebuffers (1, &frameBuffer);
	glGenRenderbuffers (1, &depthRenderBuffer);
	glGenTextures (1, &texture);
	glBindTexture (GL_TEXTURE_2D, texture);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB,texWidth, texHeight,0,GL_RGB )
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindRenderbuffer (GL_RENDERBUFFER, depthRenderBuffer);
	glRenderbufferStorage (GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, texWidth, texHeight);
	glFramebufferRenderbuffer (GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);
	*/
	Input::getInstance ();
	ResourceManager::getInstance ()->setReadDocument ("resourceManager.xml");
	ResourceManager::getInstance ()->loadResources (ResourceManager::getInstance ()->doc.getRootNode ());

	SceneManager::getInstance ()->setReadDocument ("sceneManager.xml");
	SceneManager::getInstance ()->Init (SceneManager::getInstance ()->doc.getRootNode ());
	SceneManager::getInstance ()->InitialiseObject ();

	GameManager::getInstance ()->SetContext (esContext);

	return 0;
}

void Draw (ESContext* esContext)
{
	SceneManager::getInstance ()->Draw ();
	eglSwapBuffers (esContext->eglDisplay, esContext->eglSurface);
}


void Update (ESContext* esContext, float deltaTime)
{
	Time::deltaTime = deltaTime;
	Time::time += deltaTime;
	if (Time::time >= 1)
		Time::time = Time::time - 1;
	_time += deltaTime;
	SceneManager::getInstance ()->activeCamera->setDeltaTime (deltaTime);

	if (_time >= 0.01)
	{
		GameManager::getInstance ()->Update ();

		if (Input::GetKeyUp ('P'))
			SceneManager::getInstance ()->wired = !SceneManager::getInstance ()->wired;
		SceneManager::getInstance ()->Update (deltaTime);

		Input::ResetKeyState ();
		_time = 0;
	}
}

void CleanUp ()
{
	//glDeleteBuffers(1, &modelBuffer);
	//glDeleteTextures (1, &texture);
}

int _tmain (int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ESContext esContext;

	esInitContext (&esContext);

	esCreateWindow (&esContext, "Hello Triangle", window::screenWidth, window::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH | ES_WINDOW_STENCIL);

	if (Init (&esContext) != 0)
		return 0;
	//SceneManager::getInstance ()->activeCamera->updateWorldView ();
	esRegisterDrawFunc (&esContext, Draw);
	esRegisterUpdateFunc (&esContext, Update);
	esRegisterKeyFunc (&esContext, Input::Update);

	esMainLoop (&esContext);

	//releasing OpenGL resources
	CleanUp ();


	printf ("Press any key...\n");
	_getch ();


	return 0;
}

