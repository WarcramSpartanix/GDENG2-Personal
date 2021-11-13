#include "CreditsScreen.h"
#include "Utility.h"
#include <iostream>

CreditsScreen::CreditsScreen() : AUIScreen(ScreenNames::CREDITS_SCREEN)
{
	if (!(Utility::LoadTextureFromFile("textures/DLSU Logo.png", &my_texture, &m_logo_width, &m_logo_height)))
		std::cout << "Failed to Load image";
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::drawUI()
{
	if (m_isActive)
	{
		ImGui::Begin("Credits", &m_isActive);

		ImGui::Image((void*)my_texture, ImVec2(m_logo_width, m_logo_height));
		ImGui::Text("Scene Editor V0.01");
		ImGui::Text("Developed By: Warren Lucenara");
		ImGui::Text("");
		ImGui::Text("Acknowledgements");
		ImGui::Text("Sir Neil");
		ImGui::Text("Pardcode");
		ImGui::Text("VeryGood");
		ImGui::Text("My Parents");
		ImGui::Text("Oxygen");


		ImGui::End();
	}
}


