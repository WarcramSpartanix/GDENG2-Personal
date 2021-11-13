#pragma once
#include "ResourceManager.h"
#include <string>

class MeshManager : public ResourceManager
{
public:
	static MeshManager* getInstance();
	static bool destroy();

	MeshPtr createMeshFromFile(const wchar_t* file_path);

protected:
	// Inherited via ResourceManager
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) override;


private:

	static MeshManager* sharedInstance;

	MeshManager();
	~MeshManager();
};

