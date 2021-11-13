#include "ColorPickerScreen.h"

ColorPickerScreen::ColorPickerScreen() : AUIScreen(ScreenNames::COLOR_PICKER_SCREEN)
{
}

ColorPickerScreen::~ColorPickerScreen()
{
}

void ColorPickerScreen::drawUI()
{
	if (m_isActive)
	{
		ImGui::Begin("ColorPicker");
		ImGui::ColorEdit4("Color", m_color);
		ImGui::End();
	}
}
