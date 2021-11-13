#pragma once
#include "AUIScreen.h"
#include "extra/imfilebrowser.h"


class MenuScreen :
    public AUIScreen
{
public:
    MenuScreen();
    ~MenuScreen();

    void Undo();
    void Redo();


	virtual void drawUI() override;

	friend class UIManager;

private:
    ImGui::FileBrowser saveDialog;
    ImGui::FileBrowser loadDialog;

};

