#include "MeshManager.h"
#include "Mesh.h"

MeshManager* MeshManager::sharedInstance = nullptr;

MeshManager::MeshManager() : ResourceManager()
{
}

MeshManager::~MeshManager()
{
}

MeshManager* MeshManager::getInstance()
{
	if (sharedInstance == nullptr)
		sharedInstance = new MeshManager();

	return sharedInstance;
}

MeshPtr MeshManager::createMeshFromFile(const wchar_t* file_path)
{

	return std::static_pointer_cast<Mesh>(createResourceFromFile(file_path));
}

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	Mesh* tex = nullptr;
	try
	{
		tex = new Mesh(file_path);
	}
	catch (...)
	{
	}


	return tex;
}