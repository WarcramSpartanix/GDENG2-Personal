#include "AppWindow.h"
#include <Windows.h>
#include "Vertex.h"
#include "ObjLoader.h"
#include "EngineTime.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "RenderSystem.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "MeshObject.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "EngineBackend.h"

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::update()
{
	Matrix4x4 temp;
	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	Vector3D new_pos = m_world_camera.getTranslation() + world_cam.getZDirection() * (m_forward*0.1f);
	new_pos += world_cam.getXDirection() * (m_rightward * 0.1f);

	world_cam.setTranslation(new_pos);

	m_world_camera = world_cam;

	world_cam.inverse();

	m_view_matrix.setMatrix(world_cam);
}

void AppWindow::onCreate()
{
	InputSystem::getInstance()->addListener(this);
	UIManager::getInstance()->init(&m_hwnd);
	m_width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	m_height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;

	SceneCameraHandler::getInstance()->getCamera()->setDimensions(m_width, m_height);

	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::getInstance()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();
	ShaderManager::getInstance();
	GameObjectManager::getInstance();
	
	TextureManager::getInstance();
	MeshManager::getInstance();
	BaseComponentSystem::getInstance();

	//GameObjectManager::getInstance()->addObject(new MeshObject("Teapot", L"Obj\\teapot.obj", L"textures\\brick.png"));
	//GameObjectManager::getInstance()->addObject(new MeshObject("Bunny", L"Obj\\bunny.obj", nullptr));
	//GameObjectManager::getInstance()->addObject(new MeshObject("Armadillo", L"Obj\\armadillo.obj", nullptr));

	bool preloadMesh = false;
	if (preloadMesh)
	{
		MeshManager::getInstance()->createMeshFromFile(L"Obj\\teapot.obj");
		MeshManager::getInstance()->createMeshFromFile(L"Obj\\bunny.obj");
		MeshManager::getInstance()->createMeshFromFile(L"Obj\\armadillo.obj");
	}

	constant cc;
	cc.m_time = 0;
	
}

void AppWindow::onUpdate()
{
	InputSystem::getInstance()->update();
	
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(m_swap_chain, 0, 0, 1, 1);
	
	RECT rc = this->getClientWindowRect();


	float width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	float height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setViewPortSize(width, height);


	SceneCameraHandler::getInstance()->update();

	//Game Object Update
	EngineBackend* backend = EngineBackend::getInstance();
	EngineMode mode = backend->getMode();

	if (mode == EngineMode::Editor)
	{
		GameObjectManager::getInstance()->updateObjects();
	}
	else if (mode == EngineMode::Play)
	{
		GameObjectManager::getInstance()->updateObjects();
		BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAll();
	}
	else if (mode == EngineMode::Paused)
	{
		if (backend->insideFrameStep())
		{
			GameObjectManager::getInstance()->updateObjects();
			BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAll();
			backend->endFrameStep();
		}
	}

	// Render
	GameObjectManager::getInstance()->renderObjects(width, height);

	// UI draw
	UIManager::getInstance()->drawUI();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->focus(true);
}

void AppWindow::onKillFocus()
{
	//InputSystem::getInstance()->removeListener(this);
	InputSystem::getInstance()->focus(false);
}

void AppWindow::onKeyDown(int key)
{

}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
}
