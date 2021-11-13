#include "RigidPlane.h"
#include "PhysicsComponent.h"

RigidPlane::RigidPlane(std::string name) : Cube(name)
{
	setScale(10, 0.1f, 10);
	updateLocalMatrix();
	this->type = PrimitiveType::PLANE;

	PhysicsComponent* comp = new PhysicsComponent("PhysicsComponentPlane", this);
	comp->getRigidBody()->setType(BodyType::KINEMATIC);
	addComponent(comp);
}

RigidPlane::~RigidPlane()
{
}
