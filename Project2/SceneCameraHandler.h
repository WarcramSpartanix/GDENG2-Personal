#pragma once
#include "Camera.h"


class SceneCameraHandler
{
public:
	static SceneCameraHandler* getInstance();

	Camera* getCamera();
	void update();
	Matrix4x4 getCameraViewMatrix();
	Matrix4x4 getProjectionMatrix();
	
private:
	SceneCameraHandler();
	~SceneCameraHandler();
	
	static SceneCameraHandler* sharedInstance;

private:
	Camera* m_camera;
};

