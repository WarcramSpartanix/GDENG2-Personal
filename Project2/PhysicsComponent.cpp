#include "PhysicsComponent.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "Vector3D.h"
#include "AGameObject.h"

PhysicsComponent::PhysicsComponent(std::string name, AGameObject* owner) : AComponent(name, ComponentType::Physics, owner)
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
	PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();


	Vector3D scale = getOwner()->getLocalScale();
	Transform transform; transform.setFromOpenGL(getOwner()->getPhysicsLocalMatrix());
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));

	m_rigidBody = physicsWorld->createRigidBody(transform);
	transform.setToIdentity();
	m_rigidBody->addCollider(boxShape, transform);
	m_rigidBody->updateMassPropertiesFromColliders();
	m_rigidBody->setMass(m_mass);

	if (getOwner()->getType() != PrimitiveType::PLANE)
		m_rigidBody->setType(BodyType::DYNAMIC);
	else
		m_rigidBody->setType(BodyType::KINEMATIC);

	transform = this->m_rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);;

	this->getOwner()->setLocalMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
	reactphysics3d::PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();
	if(m_rigidBody!= nullptr)
		physicsWorld->destroyRigidBody(this->m_rigidBody);
	BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
}

void PhysicsComponent::perform(float deltaTime)
{
	if (getOwner()->isEnabled())
	{
		const Transform transform = m_rigidBody->getTransform();
		reactphysics3d::Vector3 newPos;
		reactphysics3d::Quaternion newRot;
		newPos = transform.getPosition();
		newRot = transform.getOrientation();

		this->getOwner()->setRotation(newRot.x, newRot.y, newRot.z);
		this->getOwner()->setPosition(newPos.x, newPos.y, newPos.z);
	}
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return m_rigidBody;
}

void PhysicsComponent::reset()
{
	PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

	if (m_rigidBody != nullptr)
		physicsWorld->destroyRigidBody(m_rigidBody);

	Vector3D scale = getOwner()->getLocalScale();
	Transform transform; transform.setFromOpenGL(getOwner()->getPhysicsLocalMatrix());
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));

	m_rigidBody = physicsWorld->createRigidBody(transform);
	transform.setToIdentity();
	m_rigidBody->addCollider(boxShape, transform);
	m_rigidBody->updateMassPropertiesFromColliders();
	m_rigidBody->setMass(m_mass);
	if (getOwner()->getType() != PrimitiveType::PLANE)
		m_rigidBody->setType(BodyType::DYNAMIC);
	else
		m_rigidBody->setType(BodyType::KINEMATIC);

	transform = this->m_rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);;

	this->getOwner()->setLocalMatrix(matrix);
}

