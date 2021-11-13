#include "SceneCameraHandler.h"
#include "EngineTime.h"
#include "InputSystem.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = nullptr;

SceneCameraHandler* SceneCameraHandler::getInstance()
{
	if (sharedInstance == nullptr)
		sharedInstance = new SceneCameraHandler();

	return sharedInstance;
}

Camera* SceneCameraHandler::getCamera()
{
	return m_camera;
}

void SceneCameraHandler::update()
{
	if (m_camera != nullptr)
		m_camera->update(EngineTime::getDeltaTime());
}

Matrix4x4 SceneCameraHandler::getCameraViewMatrix()
{
	return m_camera->getViewMatrix();
}

Matrix4x4 SceneCameraHandler::getProjectionMatrix()
{
	return m_camera->getProjMatrix();
}

SceneCameraHandler::SceneCameraHandler()
{
	m_camera = new Camera();
	InputSystem::getInstance()->addListener(m_camera);
}

SceneCameraHandler::~SceneCameraHandler()
{
}


