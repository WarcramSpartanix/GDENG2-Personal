#pragma once

class PhysicsSystem;

class BaseComponentSystem
{
public:
	static BaseComponentSystem* getInstance();

	PhysicsSystem* getPhysicsSystem();
private:
	BaseComponentSystem();
	~BaseComponentSystem();

	static BaseComponentSystem* sharedInstance;

	PhysicsSystem* m_physicsSystem;
};

