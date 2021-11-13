#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Cube.h"
#include "Plane.h"
#include "InputListener.h"
#include "Point.h"
#include <vector>
#include "Prerequisites.h"


class AppWindow :
    public Window, public InputListener
{
public:
    AppWindow();
    ~AppWindow();

    void update();
	
    // Inherited via Window
    virtual void onCreate() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
    virtual void onFocus() override;
    virtual void onKillFocus() override;

	void onKeyDown(int key) override;
	void onKeyUp(int key) override;
	void onMouseMove(const Point& mouse_pos) override;
	void onLeftMouseDown(const Point& mouse_pos) override;
	void onLeftMouseUp(const Point& mouse_pos) override;
	void onRightMouseDown(const Point& mouse_pos) override;
	void onRightMouseUp(const Point& mouse_pos) override;

private:
    SwapChainPtr m_swap_chain;
    VertexBufferPtr m_vb;
    IndexBufferPtr m_ib;
    VertexShaderPtr m_vs;
    PixelShaderPtr m_ps;
    ConstantBufferPtr m_cb;
	
private:

    float m_time = 0;
    float m_delta_pos = 0;
    float m_delta_scale = 0;

    float m_rot_x = 0;
    float m_rot_y = 0;
    float m_forward = 0.0f;
    float m_rightward = 0.0f;

    float m_width;
    float m_height;

    Matrix4x4 m_view_matrix;
    Matrix4x4 m_world_camera;
};

