#include "Singleton.h"

Singleton* Singleton::sharedInstance = nullptr;

Singleton* Singleton::getInstance()
{
	if (sharedInstance == nullptr)
		startUp();

	return sharedInstance;
}

bool Singleton::startUp()
{
	sharedInstance = new Singleton();
}

bool Singleton::shutDown()
{
}

bool Singleton::init()
{
}
