#pragma once
#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "ScreenNames.h"

class UIManager;

class AUIScreen
{
protected:
	AUIScreen(std::string name);
	~AUIScreen();

	std::string getName();
	virtual void drawUI() = 0;

	std::string m_name;

	bool m_isActive = true;
public:
	void activate();
	void deactivate();

private:
	friend class UIManager;
};

