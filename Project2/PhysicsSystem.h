#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;
class PhysicsComponent;

class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void registerComponent(PhysicsComponent* component);
	void unregisterComponent(PhysicsComponent* component);
	void unregisterComponentByName(std::string name);
	PhysicsComponent* findComponentByName(std::string name);
	std::vector<PhysicsComponent*> getAllComponents();

	void updateAll();
	PhysicsWorld* getPhysicsWorld();
	PhysicsCommon* getPhysicsCommon();

private:
	std::vector<PhysicsComponent*> m_componentList;
	std::unordered_map<std::string, PhysicsComponent*> m_componentMap;

	PhysicsCommon* m_physicsCommon;
	PhysicsWorld* m_physicsWorld;
};

