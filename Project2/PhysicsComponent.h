#pragma once
#include "AComponent.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent :
    public AComponent
{
public:
    PhysicsComponent(std::string name, AGameObject* owner);
    ~PhysicsComponent();

    virtual void perform(float deltaTime) override;

    RigidBody* getRigidBody();
    void reset() override;

private:
    float m_mass = 1.0f; // kg
    RigidBody* m_rigidBody;

};

