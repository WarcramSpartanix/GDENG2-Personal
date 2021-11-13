#include "RigidCube.h"
#include "PhysicsComponent.h"

RigidCube::RigidCube(std::string name): Cube(name)
{
	setPosition(0, 3, 0);
	updateLocalMatrix();
	addComponent(new PhysicsComponent("PhysicsComponent", this));
}

RigidCube::~RigidCube()
{
}
