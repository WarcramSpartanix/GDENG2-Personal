#pragma once
#include <d3d11.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include <vector>
#include <unordered_map>
#include "AUIScreen.h"

class UIManager
{
public:
	static UIManager* getInstance();
	void init(HWND* hwnd);
	void drawUI();

	void addScreen(std::string name, AUIScreen* screen);
	AUIScreen* getScreen(std::string name);

public:
	static float WINDOW_WIDTH;
	static float WINDOW_HEIGHT;

private:
	std::vector<AUIScreen*> uiList;
	std::unordered_map<std::string, AUIScreen*> uiMap;

private:
	static UIManager* sharedInstance;
	UIManager();
	~UIManager();

};

