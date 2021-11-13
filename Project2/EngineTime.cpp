#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance = nullptr;

float EngineTime::timeScale = 1.0f;

void EngineTime::initialize()
{
	sharedInstance = new EngineTime();
}

double EngineTime::getDeltaTime()
{
	return sharedInstance->deltaTime;
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = sharedInstance->end - sharedInstance->start;

	sharedInstance->deltaTime = elapsedTime.count() * sharedInstance->timeScale;
}
