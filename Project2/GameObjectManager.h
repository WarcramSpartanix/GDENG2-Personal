#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "AGameObject.h"

class GameObjectManager
{
public:

	static GameObjectManager* getInstance();

	AGameObject* findObjectByName(std::string name);
	std::vector<AGameObject*> getAllObjects();
	void deleteAllObjects();
	void updateObjects();
	void renderObjects(int width, int height);
	void addObject(AGameObject* gameObject);
	void deleteObject(AGameObject* gameObject);
	void deleteObject(std::string name);
	void setSelectedObject(std::string name);
	void resetAllComponents();

	void createObjectFromFile(std::string name, PrimitiveType type, Vector3D position, Vector3D rotation, Vector3D scale, int hasRigidBody);

	AGameObject* selectedObject = nullptr;

private:
	GameObjectManager();
	~GameObjectManager();
	static GameObjectManager* sharedInstance;

	std::unordered_map<std::string, AGameObject*> m_gameObjectMap;
	std::vector<AGameObject*> m_gameObjectList;


};