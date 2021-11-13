#include "AComponent.h"


AComponent::AComponent(std::string name, ComponentType type, AGameObject* owner) 
    : m_name(name), m_type(type), m_owner(owner)
{
}

AComponent::~AComponent()
{
}

void AComponent::attachOwner(AGameObject* owner)
{
    m_owner = owner;
}

/// <summary>
/// detachOwner will delete component after detach
/// </summary>
void AComponent::detachOwner()
{
    m_owner = nullptr;
}

AGameObject* AComponent::getOwner()
{
    return m_owner;
}

ComponentType AComponent::getType()
{
    return m_type;
}

std::string AComponent::getName()
{
    return m_name;
}
