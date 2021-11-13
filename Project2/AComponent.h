#pragma once
#include <string>
#include <iostream>

enum class ComponentType
{
	NotSet, Script, Renderer, Input, Physics
};

class AGameObject;

class AComponent
{
public:
	AComponent(std::string name, ComponentType type, AGameObject* owner);
	virtual ~AComponent();

	void attachOwner(AGameObject* owner);
	void detachOwner();
	AGameObject* getOwner();
	ComponentType getType();
	std::string getName();
	
	virtual void reset() = 0;
	virtual void perform(float deltaTime) = 0;

private:
	AGameObject* m_owner;
	ComponentType m_type;
	std::string m_name;
};

