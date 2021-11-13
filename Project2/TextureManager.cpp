#include "TextureManager.h"
#include "Texture.h"

TextureManager* TextureManager::sharedInstance = nullptr;

TextureManager::TextureManager() : ResourceManager()
{
}

TextureManager::~TextureManager()
{
}

TextureManager* TextureManager::getInstance()
{
	if (sharedInstance == nullptr)
		sharedInstance = new TextureManager();

	return sharedInstance;
}

TexturePtr TextureManager::createTextureFromFile(const wchar_t* file_path)
{

	return std::static_pointer_cast<Texture>(createResourceFromFile(file_path));
}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	Texture* tex = nullptr;
	try
	{
		tex = new Texture(file_path);
	}
	catch (...)
	{
	}


	return tex;
}
