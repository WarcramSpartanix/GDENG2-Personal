#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "EngineTime.h"

PhysicsSystem::PhysicsSystem()
{
    m_physicsCommon = new PhysicsCommon();
    PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 50;
    settings.gravity = Vector3(0, -9.81, 0);
    m_physicsWorld = m_physicsCommon->createPhysicsWorld(settings);
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
    m_componentList.push_back(component);
    m_componentMap[component->getName()] = component;
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
    if (m_componentMap[component->getName()] != nullptr)
    {
        m_componentMap.erase(component->getName());
        int index = 0;
        for (int index = 0; index < m_componentList.size(); index++)
        {
            if (m_componentList[index] == component);
            break;
        }
        
        if (index < m_componentList.size())
        {
            m_componentList[index]->detachOwner();
            m_componentList.erase(m_componentList.begin() + index);
        }
    }
}

void PhysicsSystem::unregisterComponentByName(std::string name)
{
    if (m_componentMap[name] != nullptr)
        unregisterComponent(m_componentMap[name]);
}

PhysicsComponent* PhysicsSystem::findComponentByName(std::string name)
{
    if (m_componentMap[name] == nullptr)
        std::cout << "Component " << name << " does not exist" << std::endl;
    return m_componentMap[name];
}

std::vector<PhysicsComponent*> PhysicsSystem::getAllComponents()
{
    return m_componentList;
}

void PhysicsSystem::updateAll()
{
    if (m_componentList.size() > 0)
    {
        m_physicsWorld->update(EngineTime::getDeltaTime());
    }
    for (int i = 0; i < m_componentList.size(); i++)
    {
        m_componentList[i]->perform(EngineTime::getDeltaTime());
    }
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
    return m_physicsWorld;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
    return m_physicsCommon;
}
