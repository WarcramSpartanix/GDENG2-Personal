#pragma once

#include <d3d11.h>
#include "Prerequisites.h"


class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);
	~DeviceContext();

	void clearRenderTargetColor(SwapChainPtr swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBufferPtr vertex_buffer);
	void setVertexBuffer(TexturedVertexBufferPtr textured_vertex_buffer);
	void setIndexBuffer(IndexBufferPtr index_buffer);
	
	void drawPointList(UINT vertex_count, UINT start_vertex_index);
	void drawLineList(UINT vertex_count, UINT start_vertex_index);
	void drawLineStrip(UINT vertex_count, UINT start_vertex_index);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	
	void setViewPortSize(UINT width, UINT height);

	void setVertexShader(VertexShaderPtr vertex_shader);
	void setPixelShader(PixelShaderPtr pixel_shader);

	void setTexture(TexturePtr texture);

	void setConstantBuffer(VertexShaderPtr vertex_shader, ConstantBufferPtr buffer);
	void setConstantBuffer(PixelShaderPtr pixel_shader, ConstantBufferPtr buffer);
	void setConstantBuffer(ConstantBufferPtr buffer);
	
	ID3D11DeviceContext* getDeviceContext();

private:
	ID3D11DeviceContext* m_device_context;
	RenderSystem* m_system = nullptr;
private:
	friend class ConstantBuffer;
};

