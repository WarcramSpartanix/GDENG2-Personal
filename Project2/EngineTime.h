#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

class EngineTime
{
public:
	static void initialize();
	static double getDeltaTime();
	
	static float timeScale;

private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&) {};
	EngineTime& operator = (EngineTime const&) {};

	static EngineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0f;

	static void LogFrameStart();
	static void LogFrameEnd();

	friend class Window;
	friend class AppWindow;
	
};

