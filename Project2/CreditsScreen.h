#pragma once
#include "AUIScreen.h"
#include "extra/stb_image.h"
#include <d3d11.h>

class CreditsScreen :
    public AUIScreen
{

public:
    CreditsScreen();
    ~CreditsScreen();

    // Inherited via AUIScreen
    virtual void drawUI() override;
private:
    int m_logo_height;
    int m_logo_width;
    ID3D11ShaderResourceView* my_texture = nullptr;


};

