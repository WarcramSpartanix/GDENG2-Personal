#pragma once
#include "AUIScreen.h"
class ColorPickerScreen :
    public AUIScreen
{
public:
    ColorPickerScreen();
    ~ColorPickerScreen();



    // Inherited via AUIScreen
    virtual void drawUI() override;

private:
    float m_color[4] = {0.0f,1.0f,0.0f,1.0f};
};

