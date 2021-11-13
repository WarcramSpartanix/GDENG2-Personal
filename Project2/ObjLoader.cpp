#include "ObjLoader.h"
#include <iostream>
#include <fstream>
#include <vector>

ObjLoader* ObjLoader::sharedInstance = nullptr;

ObjLoader* ObjLoader::getInstance()
{
	if (sharedInstance == nullptr)
		startUp();

	return sharedInstance;
}

bool ObjLoader::startUp()
{
	sharedInstance = new ObjLoader();
	return true;
}

bool ObjLoader::shutDown()
{
	delete sharedInstance;
	return true;
}

void ObjLoader::loadObjFromFile(std::string filename, obj* obj)
{
	if(obj == nullptr)
		return;

	std::string myText;
	std::string delimiter = " ";
	// Read from the text file
	std::ifstream MyReadFile(filename);

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(MyReadFile, myText)) {
		std::string strtemp = myText.substr(0, myText.find(delimiter));
		myText.erase(0, myText.find(delimiter) + delimiter.length());
		
		if(strcmp(strtemp.c_str(), "f") == 0)
		{
			int3 int3temp;
			std::string token;

			token = myText.substr(0, myText.find(delimiter));
			int3temp.x = std::stoi(token);
			myText.erase(0, myText.find(delimiter) + delimiter.length());

			token = myText.substr(0, myText.find(delimiter));
			int3temp.y = std::stoi(token);
			myText.erase(0, myText.find(delimiter) + delimiter.length());

			token = myText.substr(0, myText.find(delimiter));
			int3temp.z = std::stoi(token);
			myText.erase(0, myText.find(delimiter) + delimiter.length());

			obj->faces.push_back(int3temp);
		}
		
		else if(strcmp(strtemp.c_str(), "v") == 0 || strcmp(strtemp.c_str(), "vn") == 0 || strcmp(strtemp.c_str(), "vt") == 0)
		{
			vec3 vec3temp;
			std::string token;
			
			token = myText.substr(0, myText.find(delimiter));
			vec3temp.x = std::stof(token);
			myText.erase(0, myText.find(delimiter) + delimiter.length());
			
			token = myText.substr(0, myText.find(delimiter));
			vec3temp.y = std::stof(token);
			myText.erase(0, myText.find(delimiter) + delimiter.length());
			
			token = myText.substr(0, myText.find(delimiter));
			vec3temp.z = std::stof(token);
			myText.erase(0, myText.find(delimiter) + delimiter.length());

			if (strcmp(strtemp.c_str(), "v") == 0)
				obj->vertices.push_back(vec3temp);
			else if (strcmp(strtemp.c_str(), "vn") == 0)
				obj->vertexNormal.push_back(vec3temp);
			else if (strcmp(strtemp.c_str(), "vt") == 0)
				obj->textureCoords.push_back(vec3temp);
		}
		
	}
	

	// Close the file
	MyReadFile.close();
}

ObjLoader::ObjLoader()
{
	
}

ObjLoader::~ObjLoader()
{
}
