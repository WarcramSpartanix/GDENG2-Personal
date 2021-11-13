#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = nullptr;

BaseComponentSystem* BaseComponentSystem::getInstance()
{
    if (sharedInstance == nullptr)
        sharedInstance = new BaseComponentSystem();
    return sharedInstance;
}

PhysicsSystem* BaseComponentSystem::getPhysicsSystem()
{

    return m_physicsSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
    m_physicsSystem = new PhysicsSystem();
}

BaseComponentSystem::~BaseComponentSystem()
{
}
