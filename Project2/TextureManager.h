#pragma once
#include "ResourceManager.h"
#include <string>

class TextureManager :
    public ResourceManager
{
public:
	static TextureManager* getInstance();

	TexturePtr createTextureFromFile(const wchar_t* file_path);

protected:
	// Inherited via ResourceManager
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) override;


private:

	static TextureManager* sharedInstance;

	TextureManager();
	~TextureManager();
};

