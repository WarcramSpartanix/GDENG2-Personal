#include <iostream>
#include "AppWindow.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"

int main()
{
	try 
	{
		GraphicsEngine::create();
		InputSystem::create();
	}
	catch (...) { return -1; }




	try
	{
		AppWindow app;


		while (app.isRun())
		{
		}
	}
	catch (...) 
	{
		GraphicsEngine::release();
		InputSystem::release();
		return -1; 
	}

	GraphicsEngine::release();
	InputSystem::release();

	return 0;
}