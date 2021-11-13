#include "ResourceManager.h"
#include <filesystem>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourcePtr ResourceManager::createResourceFromFile(const wchar_t* file_path)
{
    std::wstring full_path = std::filesystem::absolute(file_path);

    auto it = m_resource_map.find(full_path);

    if (it != m_resource_map.end())
        return it->second;
   
    Resource* raw_res = this->createResourceFromFileConcrete(full_path.c_str());

    if (raw_res)
    {
        ResourcePtr res(raw_res);
        m_resource_map[full_path] = res;
        return res;
    }

    return nullptr;
}
