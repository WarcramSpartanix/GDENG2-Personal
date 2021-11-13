#include "ScenePlayScreen.h"
#include "UIManager.h"
#include "EngineBackend.h"

ScenePlayScreen::ScenePlayScreen() : AUIScreen(ScreenNames::SCENE_PLAY_SCREEN)
{
}

ScenePlayScreen::~ScenePlayScreen()
{
}

void ScenePlayScreen::drawUI()
{
	ImGui::Begin("Scene Play Editor");
	ImGui::SetWindowPos(ImVec2(0, 20));
	ImGui::SetWindowSize(ImVec2(200, 60));

	EngineBackend* backend = EngineBackend::getInstance();
	EngineMode mode = backend->getMode();

	if (ImGui::Button(mode == EngineMode::Editor ? "play" : "stop", ImVec2(40, 18)))
	{
		if (mode == EngineMode::Editor)
			backend->setMode(EngineMode::Play);
		else
			backend->setMode(EngineMode::Editor);
	}
	ImGui::SameLine();
	if (mode != EngineMode::Editor)
	{
		if (ImGui::Button(mode == EngineMode::Play ? "pause" : "resume", ImVec2(50, 18)))
		{
			if(mode == EngineMode::Play)
				backend->setMode(EngineMode::Paused);
			else
				backend->setMode(EngineMode::Play);
		}
	}
	ImGui::SameLine();
	if (mode == EngineMode::Paused)
	{
		if (ImGui::Button("frameskip", ImVec2(75, 18)))
		{
			backend->startFrameStep();
		}
	}

	ImGui::End();
}
