#include "InspectorScreen.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "AGameObject.h"
#include "ActionHistory.h"
#include "PhysicsComponent.h"

InspectorScreen::InspectorScreen() : AUIScreen(ScreenNames::INSPECTOR_SCREEN)
{
}

InspectorScreen::~InspectorScreen()
{
}

void InspectorScreen::drawUI()
{
	ImGui::Begin("Inspector");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 275, 20));
	ImGui::SetWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT-100));

	selectedObject = GameObjectManager::getInstance()->selectedObject;

	if (selectedObject != NULL) {
		ImGui::Text("%s", selectedObject->getName().c_str());

		updateDisplay();
		bool enabled = selectedObject->isEnabled();
		if (ImGui::Checkbox("Enabled", &enabled)) 
		{ 
			selectedObject->setEnabled(enabled); 
		}
		if (ImGui::InputFloat3("Position", m_position)) 
		{ 
			updateTransform();
		}
		if (ImGui::InputFloat3("Rotation", m_rotation)) 
		{ 
			updateTransform(); 
		}
		if (ImGui::InputFloat3("Scale", m_scale)) 
		{
			updateTransform(); 
		}

		std::vector<AComponent*> componentList = selectedObject->getComponentsOfType(ComponentType::Physics);
		ImGui::Text("PhysicsComponent"); ImGui::SameLine();
		if (componentList.size() > 0)
		{
			if (ImGui::Button("RemovePhysics"))
			{
				selectedObject->removeComponent(componentList[0]);
			}
		}
		else
		{
			if (ImGui::Button("AddPhysics")) selectedObject->addComponent(new PhysicsComponent("PhysicsComponent", selectedObject));
		}

		if (ImGui::Button("Delete", ImVec2(235, 0))) 
		{
			GameObjectManager::getInstance()->deleteObject(selectedObject->getName().c_str());
		}
	}
	ImGui::End();
}

void InspectorScreen::updateDisplay()
{
	Vector3D pos = selectedObject->getLocalPosition();
	m_position[0] = pos.m_x;
	m_position[1] = pos.m_y;
	m_position[2] = pos.m_z;

	Vector3D rot = selectedObject->getLocalRotation();
	m_rotation[0] = rot.m_x;
	m_rotation[1] = rot.m_y;
	m_rotation[2] = rot.m_z;

	Vector3D scale = selectedObject->getLocalScale();
	m_scale[0] = scale.m_x;
	m_scale[1] = scale.m_y;
	m_scale[2] = scale.m_z;
}

void InspectorScreen::updateTransform()
{
	if (selectedObject != NULL) {
		ActionHistory::getInstance()->recordUndo(selectedObject);

		selectedObject->setPosition(Vector3D(m_position[0], m_position[1], m_position[2]));
		selectedObject->setRotation(Vector3D(m_rotation[0], m_rotation[1], m_rotation[2]));
		selectedObject->setScale(Vector3D(m_scale[0], m_scale[1], m_scale[2]));
	}
}