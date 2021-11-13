#include "HierarchyScreen.h"
#include "GameObjectManager.h"
#include "UIManager.h"

HierarchyScreen::HierarchyScreen() : AUIScreen(ScreenNames::HIERARCHY_SCREEN)
{
}

HierarchyScreen::~HierarchyScreen()
{
}

void HierarchyScreen::drawUI()
{
	ImGui::Begin("Hierarchy");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 525, 20));
	ImGui::SetWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT-100));

	updateObjectList();
	ImGui::End();
}

void HierarchyScreen::updateObjectList()
{
	std::vector<AGameObject*> objectList = GameObjectManager::getInstance()->getAllObjects();
	for (int i = 0; i < objectList.size(); i++) {
		std::string objectName = objectList[i]->getName();
		if (ImGui::Button(objectName.c_str(), ImVec2(235, 0))) {
			GameObjectManager::getInstance()->setSelectedObject(objectName);
		}
	}
}