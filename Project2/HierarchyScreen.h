#pragma once
#include "AUIScreen.h"
class HierarchyScreen : public AUIScreen
{
public:
	HierarchyScreen();
	~HierarchyScreen();

	virtual void drawUI() override;

private:
	void updateObjectList();
};