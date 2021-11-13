#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "GameObjectManager.h"
#include "AGameObject.h"
#include "Vector3D.h"
#include "StringUtils.h"

FileManager* FileManager::sharedInstance = nullptr;

FileManager* FileManager::getInstance()
{
    if (sharedInstance == nullptr)
        sharedInstance = new FileManager();
    return sharedInstance;
}

void FileManager::save(std::string filepath)
{
    std::vector<AGameObject*> gameobjectList = GameObjectManager::getInstance()->getAllObjects();

    std::ofstream file(filepath);

    if (file.is_open())
    {
        for (int i = 0; i < gameobjectList.size(); i++)
        {
            
            AGameObject* obj = gameobjectList[i];
            Vector3D position = obj->getLocalPosition();
            Vector3D rotation = obj->getLocalRotation();
            Vector3D scale = obj->getLocalScale();

            int hasPhysics = (obj->getComponentsOfType(ComponentType::Physics).size() > 0) ? 1 : 0;

            file << obj->getName() << std::endl;
            file << "Type: " << obj->getType() << std::endl;
            file << "Position: " << position.m_x << " " << position.m_y << " " << position.m_z << std::endl;
            file << "Rotation: " << rotation.m_x << " " << rotation.m_y << " " << rotation.m_z << std::endl;
            file << "Scale: " << scale.m_x << " " << scale.m_y << " " << scale.m_z << std::endl;
            file << "PhysicsComponent: " << hasPhysics << std::endl;
        }

        file.close();
    }
    else
        std::cout << "Error in saving file" << std::endl;
 

}

void FileManager::load(std::string filepath)
{
    std::ifstream file(filepath);

    GameObjectManager::getInstance()->deleteAllObjects();

    if (file.is_open())
    {
        std::string name;
        PrimitiveType type;
        Vector3D position;
        Vector3D rotation;
        Vector3D scale;
        int hasPhysics;

        std::string line;
        int index = 0;

        while (std::getline(file, line))
        {
            switch (index)
            {
                case 0:
                {
                    name = line;
                    index++;
                    break;
                }
                case 1:
                {
                    std::vector stringSplit = StringUtils::split(line, ' ');
                    type = (PrimitiveType) std::stoi(stringSplit[1]);
                    index++;
                    break;
                }
                case 2:
                {
                    std::vector stringSplit = StringUtils::split(line, ' ');
                    position = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
                    index++;
                    break;
                }
                case 3:
                {
                    std::vector stringSplit = StringUtils::split(line, ' ');
                    rotation = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
                    index++;
                    break;
                }
                case 4:
                {
                    std::vector stringSplit = StringUtils::split(line, ' ');
                    scale = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
                    index++;
                    break;
                }
                case 5:
                {
                    std::vector stringSplit = StringUtils::split(line, ' ');
                    hasPhysics = std::stoi(stringSplit[1]);
                    
                    GameObjectManager::getInstance()->createObjectFromFile(name, type, position, rotation, scale, hasPhysics);

                    index = 0;
                    break;
                }
            }
        }
    }
    else
        std::cout << "Error in loading file" << std::endl;
}

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}
