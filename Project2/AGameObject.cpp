#include "AGameObject.h"

AGameObject::AGameObject(std::string name)
{
	this->name = name;
	localPosition = { 0,0,0 };
	localScale = { 1,1,1 };
	localRotation = { 0,0,0 };
	localMatrix.setIdentity();
}

AGameObject::~AGameObject()
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	localPosition = { x, y, z };
}

void AGameObject::setPosition(Vector3D pos)
{
	localPosition = Vector3D(pos);
}

void AGameObject::translate(float x, float y, float z)
{
	localPosition += Vector3D(x, y, z);
}

void AGameObject::translate(Vector3D pos)
{
	localPosition += pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return localPosition;
}

void AGameObject::setScale(float x, float y, float z)
{
	localScale = { x, y, z };
}

void AGameObject::setScale(Vector3D scale)
{
	localScale = Vector3D(scale);
}

void AGameObject::scale(float x, float y, float z)
{
	localScale += Vector3D(x, y, z);
}

void AGameObject::scale(Vector3D scale)
{
	localScale += scale;
}

Vector3D AGameObject::getLocalScale()
{
	return localScale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	localRotation = { x, y, z };
}

void AGameObject::setRotation(Vector3D rot)
{
	localRotation = Vector3D(rot);
}

void AGameObject::rotate(float x, float y, float z)
{
	localRotation.m_x += x;
	localRotation.m_y += y;
	localRotation.m_z += z;
}

void AGameObject::rotate(Vector3D rot)
{
	localRotation += rot;
}

Vector3D AGameObject::getLocalRotation()
{
	return localRotation;
}

std::string AGameObject::getName()
{
	return name;
}

bool AGameObject::isEnabled()
{
	return enabled;
}

void AGameObject::setEnabled(bool value)
{
	enabled = value;
}

float* AGameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setTranslation(getLocalPosition());
	Matrix4x4 scaleMatrix;

	Vector3D rotation = getLocalRotation();
	Matrix4x4 zMatrix; zMatrix.setIdentity(); zMatrix.setRotationZ(rotation.getValues().z);
	Matrix4x4 yMatrix; yMatrix.setIdentity(); yMatrix.setRotationY(rotation.getValues().y);
	Matrix4x4 xMatrix; xMatrix.setIdentity(); xMatrix.setRotationX(rotation.getValues().x);
	Matrix4x4 rotationMatrix; rotationMatrix.setIdentity();
	rotationMatrix = rotationMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotationMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);
	
	return allMatrix.getPointer();
}

void AGameObject::setLocalMatrix(float matrix[16])
{
	Matrix4x4 matrix4;
	matrix4.setMatrix(matrix);
	
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(localScale);
	Matrix4x4 transMatrix; transMatrix.setTranslation(localPosition);
	this->localMatrix = scaleMatrix.multiplyTo(transMatrix.multiplyTo(matrix4));

	m_overrideMatrix = true;
}

void AGameObject::updateLocalMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setTranslation(getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(getLocalScale());

	Vector3D rotation = getLocalRotation();
	Matrix4x4 zMatrix; zMatrix.setIdentity(); zMatrix.setRotationZ(rotation.getValues().z);
	Matrix4x4 yMatrix; yMatrix.setIdentity(); yMatrix.setRotationY(rotation.getValues().y);
	Matrix4x4 xMatrix; xMatrix.setIdentity(); xMatrix.setRotationX(rotation.getValues().x);
	Matrix4x4 rotationMatrix; rotationMatrix.setIdentity();
	rotationMatrix = rotationMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotationMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);
	this->localMatrix.setMatrix(allMatrix);
}

void AGameObject::setType(PrimitiveType type)
{
	this->type = type;
}

void AGameObject::addComponent(AComponent* component)
{
	component->attachOwner(this);
	if (m_componentMap[component->getName()] == nullptr)
	{
		this->m_componentList.push_back(component);
		this->m_componentMap[component->getName()] = component;
	}
	else
	{
		std::cout << "Attempted to add an already existing component name" << std::endl;
	}
}

void AGameObject::removeComponent(AComponent* component)
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
			delete m_componentList[index];
			m_componentList.erase(m_componentList.begin() + index);
		}

		
	}
}

AComponent* AGameObject::findComponentByName(std::string name)
{
	if (m_componentMap[name] == nullptr)
		std::cout << "Component " << name << " does not exist" << std::endl;
	return m_componentMap[name];
}

std::vector<AComponent*> AGameObject::getComponentsOfType(ComponentType type)
{
	std::vector<AComponent*> temp;

	for (int i = 0; i < m_componentList.size(); i++)
	{
		if (m_componentList[i]->getType() == type)
			temp.push_back(m_componentList[i]);
	}

	return temp;
}

PrimitiveType AGameObject::getType()
{
	return type;
}
