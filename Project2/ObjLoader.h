#pragma once
#include <string>
#include "Vertex.h"

class ObjLoader
{
public:
	static ObjLoader* getInstance();

	static bool startUp();
	static bool shutDown();

	void static loadObjFromFile(std::string filename, obj* obj);
	
private:
	static ObjLoader* sharedInstance;
	ObjLoader();
	~ObjLoader();
};

