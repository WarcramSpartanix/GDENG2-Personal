#pragma once
#include <string>

class FileManager
{
public:
	static FileManager* getInstance();
	void save(std::string filepath);
	void load(std::string filepath);

private:
	static FileManager* sharedInstance;

	FileManager();
	~FileManager();
};

