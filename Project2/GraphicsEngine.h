#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

class GraphicsEngine
{
public:
	GraphicsEngine();	//Initialize the GraphicsEngine and DirectX 11 Device
	~GraphicsEngine();	// Release all the resources loaded

	RenderSystem* getRenderSystem();
	

public: 
	static GraphicsEngine* getInstance();
	static void create();
	static void release();

private:
	static GraphicsEngine* sharedInstance;

private:
	RenderSystem* m_render_system = nullptr;

};

