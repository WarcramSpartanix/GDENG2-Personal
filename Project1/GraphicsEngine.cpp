#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include <d3dcompiler.h>

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;

GraphicsEngine::GraphicsEngine()
{
}

GraphicsEngine::~GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
    sharedInstance = new GraphicsEngine();
    D3D_DRIVER_TYPE driver_types[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };
    UINT num_driver_types = ARRAYSIZE(driver_types);

    D3D_FEATURE_LEVEL feature_levels[] =
    {
        D3D_FEATURE_LEVEL_11_0
    };
    UINT num_feature_levels = ARRAYSIZE(feature_levels);


    HRESULT res = 0;
    for (UINT driver_types_index = 0; driver_types_index < num_driver_types;)
    {
        res = D3D11CreateDevice(NULL, driver_types[driver_types_index], NULL, NULL, feature_levels,
        num_feature_levels, D3D11_SDK_VERSION, &sharedInstance->m_d3d_device, &sharedInstance->m_feature_level, &sharedInstance->m_imm_context);

        if (SUCCEEDED(res))
            break;
        
        ++driver_types_index;
    }

    if (FAILED(res))
    {
        return false;
    }

    sharedInstance->m_imm_device_context = new DeviceContext(sharedInstance->m_imm_context);

    sharedInstance->m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&sharedInstance->m_dxgi_device);
    sharedInstance->m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&sharedInstance->m_dxgi_adapter);
    sharedInstance->m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&sharedInstance->m_dxgi_factory);
 
    return true;
}

bool GraphicsEngine::release()
{
    if (sharedInstance->m_vs)sharedInstance->m_vs->Release();
    if (sharedInstance->m_ps)sharedInstance->m_ps->Release();

    if (sharedInstance->m_vsblob)sharedInstance->m_vsblob->Release();
    if (sharedInstance->m_psblob)sharedInstance->m_psblob->Release();

    sharedInstance->m_d3d_device->Release();
    sharedInstance->m_dxgi_device->Release();
    sharedInstance->m_dxgi_adapter->Release();

    sharedInstance->m_imm_device_context->release();
    sharedInstance->m_d3d_device->Release();
    return true;
}

SwapChain* GraphicsEngine::createSwapChain()
{
    return new SwapChain();
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
    return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{

    return new VertexBuffer();
}

ConstantBuffer* GraphicsEngine::createConstantBuffer()
{
    return new ConstantBuffer();
}

VertexShader* GraphicsEngine::createVertexShader(const void* shader_byte_code, size_t byte_size_code)
{
    VertexShader* vs = new VertexShader();
    if (!vs->init(shader_byte_code, byte_size_code))
    {
        vs->release();
        return nullptr;
    }
	
    return vs;
}

PixelShader* GraphicsEngine::createPixelShader(const void* shader_byte_code, size_t byte_size_code)
{
    PixelShader* ps = new PixelShader();
    if (!ps->init(shader_byte_code, byte_size_code))
    {
        ps->release();
        return nullptr;
    }

    return ps;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
    ID3DBlob* error_blob = nullptr;
    if(!SUCCEEDED( ::D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, & error_blob)))
    {
        if (error_blob)
            error_blob->Release();
        return false;
    }

    *shader_byte_code = m_blob->GetBufferPointer();
    *byte_code_size = m_blob->GetBufferSize();
	
    return true;
}

bool GraphicsEngine::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code,
	size_t* byte_code_size)
{
    ID3DBlob* error_blob = nullptr;
    if (!SUCCEEDED(::D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
    {
        if (error_blob)
            error_blob->Release();
        return false;
    }

    *shader_byte_code = m_blob->GetBufferPointer();
    *byte_code_size = m_blob->GetBufferSize();

    return true;
}

void GraphicsEngine::releaseCompiledShader()
{
    if (m_blob)
        m_blob->Release();
}

GraphicsEngine* GraphicsEngine::getInstance()
{
    return sharedInstance;
}
