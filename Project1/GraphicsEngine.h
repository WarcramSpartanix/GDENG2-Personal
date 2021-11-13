#pragma once

#include <d3d11.h>

class SwapChain;
class DeviceContext;
class ConstantBuffer;
class VertexBuffer;
class VertexShader;
class PixelShader;

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	
	//Initialize the GraphicsEngine and DirectX 11 Device
	static bool init();
	// Release all the resources loaded
	static bool release();

public:
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();
	VertexBuffer* createVertexBuffer();
	ConstantBuffer* createConstantBuffer();
	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_size_code);
	PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_size_code);

public:
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledShader();
	
	void getShaderBufferAndSize(void** bytecode, UINT* size);

public: 
	static GraphicsEngine* getInstance();

private:
	static GraphicsEngine* sharedInstance;
	DeviceContext* m_imm_device_context;

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;

private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory; 
	ID3D11DeviceContext* m_imm_context;

private:
	ID3DBlob* m_blob = nullptr;

	
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

private:
	friend class SwapChain;
	friend class VertexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
};

