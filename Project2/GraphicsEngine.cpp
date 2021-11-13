#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "RenderSystem.h"

#include <d3dcompiler.h>

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;

GraphicsEngine::GraphicsEngine()
{ 
    try
    {
        m_render_system = new RenderSystem();
    }
    catch (...)
    {
        throw std::exception("GraphicsEngine not created successfully");
    }
}

GraphicsEngine::~GraphicsEngine()
{ 
    delete m_render_system;
    sharedInstance = nullptr;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
    return m_render_system;
}



GraphicsEngine* GraphicsEngine::getInstance()
{
    if (sharedInstance == nullptr)
    {
        sharedInstance = new GraphicsEngine();
    }

    return sharedInstance;
}

void GraphicsEngine::create()
{
    if (sharedInstance)
    {
        throw std::exception("GraphicsEngine already created");
    }
    sharedInstance = new GraphicsEngine();
}

void GraphicsEngine::release()
{
    if (!sharedInstance) return;
    delete sharedInstance;
}
