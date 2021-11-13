#pragma once
#include <string>
#include <unordered_map>

#include "Vertex.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Prerequisites.h"

#include "AComponent.h"

enum PrimitiveType
{
	NOTSET = -1,
	CUBE = 1,
	PLANE = 2,
	SPHERE = 3,
	CAPSULE = 4
};

class GameObjectManager;
class AGameObject
{
public:
	AGameObject(std::string name);
	~AGameObject();

public:
	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	void translate(float x, float y, float z);
	void translate(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	void scale(float x, float y, float z);
	void scale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	void rotate(float x, float y, float z);
	void rotate(Vector3D rot);
	Vector3D getLocalRotation();

	std::string getName();
	bool isEnabled();
	void setEnabled(bool value);

	float* getPhysicsLocalMatrix();
	void setLocalMatrix(float matrix[16]);
	void updateLocalMatrix();

	void setType(PrimitiveType type);

	void addComponent(AComponent* component);
	void removeComponent(AComponent* component);

	AComponent* findComponentByName(std::string name);
	std::vector<AComponent*> getComponentsOfType(ComponentType type);

	PrimitiveType getType();

protected:
	std::string name;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;

	bool enabled = true;
	bool m_overrideMatrix = false;

	std::vector<AComponent*> m_componentList;
	std::unordered_map<std::string, AComponent*> m_componentMap;

	PrimitiveType type = NOTSET;
private:
	friend class GameObjectManager;
};

