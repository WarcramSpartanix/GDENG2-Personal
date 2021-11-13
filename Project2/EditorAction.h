#pragma once
#include "AGameObject.h"

class EditorAction
{
public:
	EditorAction(AGameObject* gameObject) : 
		m_name(gameObject->getName()), m_localPosition(gameObject->getLocalPosition()), 
		m_localScale(gameObject->getLocalScale()), m_localRotation(gameObject->getLocalRotation())
	{

	}
	~EditorAction()
	{
	}

	std::string m_name;
	Vector3D m_localPosition;
	Vector3D m_localScale;
	Vector3D m_localRotation;
};