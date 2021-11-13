#include "UIManager.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "DeviceContext.h"
#include "CreditsScreen.h"
#include "MenuScreen.h"
#include "ColorPickerScreen.h"
#include "InspectorScreen.h"
#include "HierarchyScreen.h"
#include "ScenePlayScreen.h"

UIManager* UIManager::sharedInstance = nullptr;
float UIManager::WINDOW_WIDTH = 1440;
float UIManager::WINDOW_HEIGHT = 800;


UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

UIManager* UIManager::getInstance()
{
	if (sharedInstance == nullptr)
		sharedInstance = new UIManager();

	return sharedInstance;
}

void UIManager::init(HWND* hwnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(*hwnd);

	ImGui_ImplDX11_Init(
		GraphicsEngine::getInstance()->getRenderSystem()->getDevice(),
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->getDeviceContext());
	ImGui::StyleColorsDark();



	// Init Default Screens

	MenuScreen* menu = new MenuScreen();
	uiList.push_back(menu);
	uiMap[ScreenNames::MENU_SCREEN] = menu;

	InspectorScreen* inspectorScreen = new InspectorScreen();
	uiList.push_back(inspectorScreen);
	uiMap[ScreenNames::INSPECTOR_SCREEN] = inspectorScreen;

	HierarchyScreen* hierarchyScreen = new HierarchyScreen();
	uiList.push_back(hierarchyScreen);
	uiMap[ScreenNames::HIERARCHY_SCREEN] = hierarchyScreen;

	ScenePlayScreen* scenePlayScreen = new ScenePlayScreen();
	uiList.push_back(scenePlayScreen);
	uiMap[ScreenNames::SCENE_PLAY_SCREEN] = scenePlayScreen;
}

void UIManager::drawUI()
{
#pragma region UI testing
	/*ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());*/
#pragma endregion

	// Create Frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//Draw Screens
	for (int i = 0; i < uiList.size(); i++)
	{
		uiList[i]->drawUI();
	}

	//Render
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::addScreen(std::string name, AUIScreen* screen)
{
	uiList.push_back(screen);
	uiMap[name] = screen;
}

AUIScreen* UIManager::getScreen(std::string name)
{
	if (uiMap.find(name) != uiMap.end())
	{
		return uiMap[name];
	}

	return nullptr;
}

