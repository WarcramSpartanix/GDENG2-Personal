#include "GameObjectManager.h"
#include "EngineTime.h"
#include "Cube.h"
#include "Plane.h"
#include "AGameObject.h"
#include "ShaderManager.h"
#include "GraphicsEngine.h"
#include "TexturedCube.h"
#include "EngineBackend.h"
#include "RigidCube.h"
#include "RigidPlane.h"
#include "PhysicsComponent.h"
#include "MeshObject.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

GameObjectManager* GameObjectManager::getInstance()
{
	if (sharedInstance == nullptr)
		sharedInstance = new GameObjectManager();
	return sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	if (m_gameObjectMap[name] != NULL) {
		return m_gameObjectMap[name];
	}
	
	return nullptr;
}

std::vector<AGameObject*> GameObjectManager::getAllObjects()
{
	return m_gameObjectList;
}

void GameObjectManager::deleteAllObjects()
{
	m_gameObjectMap.clear();

	for (int i = m_gameObjectList.size() - 1; i >= 0; i--)
	{
		delete m_gameObjectList[i];
	}
	m_gameObjectList.clear();
	selectedObject = nullptr;
}

void GameObjectManager::updateObjects()
{
	for (int i = 0; i < m_gameObjectList.size(); i++) {
		if (m_gameObjectList[i]->isEnabled()) {
			m_gameObjectList[i]->update(EngineTime::getDeltaTime());
		}
	}
}

void GameObjectManager::renderObjects(int width, int height)
{
	for (int i = 0; i < m_gameObjectList.size(); i++) {
		if (m_gameObjectList[i]->isEnabled()) {
			m_gameObjectList[i]->draw(width, height);
		}
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	if (findObjectByName(gameObject->getName()) != nullptr)
	{
		int count = 1;
		std::string newName = gameObject->getName() + "(" + std::to_string(count) + ")";
		while (findObjectByName(newName) != nullptr)
		{
			count++;
			newName = gameObject->getName() + "(" + std::to_string(count) + ")";
		}
		gameObject->name = newName;
	}

	m_gameObjectMap[gameObject->getName()] = gameObject;
	m_gameObjectList.push_back(gameObject);
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	m_gameObjectMap.erase(gameObject->getName());

	for (int i = 0; i < m_gameObjectList.size(); i++) {
		if (m_gameObjectList[i] == gameObject) {
			m_gameObjectList.erase(m_gameObjectList.begin() + i);
			break;
		}
	}

	if(EngineBackend::getInstance()->getMode() == EngineMode::Editor)
		delete gameObject;
}

void GameObjectManager::deleteObject(std::string name)
{
	AGameObject* object = findObjectByName(name);

	if (object != NULL) {
		if(object == selectedObject)
			selectedObject = nullptr;
		deleteObject(object);
	}
}

void GameObjectManager::setSelectedObject(std::string name)
{
	if (m_gameObjectMap[name] != NULL) {
		selectedObject = m_gameObjectMap[name];
	}
}

void GameObjectManager::resetAllComponents()
{
	for (int i = 0; i < m_gameObjectList.size(); i++)
	{
		for (int j = 0; j < m_gameObjectList[i]->m_componentList.size(); j++)
		{
			m_gameObjectList[i]->m_componentList[j]->reset();
		}
	}
}

void GameObjectManager::createObjectFromFile(std::string name, PrimitiveType type, Vector3D position, Vector3D rotation, Vector3D scale, int hasRigidBody)
{
	AGameObject* obj = nullptr;

	switch (type)
	{
	case NOTSET:
		break;
	case CUBE:
		obj = new Cube(name);
		break;
	case PLANE:
		obj = new Plane(name);
		break;
	case SPHERE:
		obj = new MeshObject("Sphere", L"Obj\\sphere.obj", L"textures\\brick.png");
		obj->setType(PrimitiveType::SPHERE);
		break;
	case CAPSULE:
		obj = new MeshObject("Capsule", L"Obj\\Capsule.obj", L"textures\\brick.png");
		obj->setType(PrimitiveType::CAPSULE);
		break;
	default:
		break;
	}


	if (obj != nullptr)
	{
		obj->setPosition(position);
		obj->setRotation(rotation);
		obj->setScale(scale);
		obj->updateLocalMatrix();
		if (hasRigidBody)
			obj->addComponent(new PhysicsComponent("PhysicsComponent", obj));
	}

	addObject(obj);

}

