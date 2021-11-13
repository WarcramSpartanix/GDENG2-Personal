#pragma once
class Singleton
{
public:
	static Singleton* getInstance();

	static bool startUp();
	static bool shutDown();
	
private:
	static Singleton* sharedInstance;
	bool init();
};

