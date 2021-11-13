#pragma once
#include "AUIScreen.h"

class AGameObject;
class InspectorScreen : public AUIScreen
{
public:
	InspectorScreen();
	~InspectorScreen();


	virtual void drawUI() override;

private:
	void updateDisplay();
	void updateTransform();

	float m_position[3];
	float m_rotation[3];
	float m_scale[3];

	AGameObject* selectedObject = nullptr;
};
