#pragma once
#include <d3d11.h>
#include "Prerequisites.h"


class TexturedVertexBuffer
{
public:
	TexturedVertexBuffer(void* m_list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader, RenderSystem* system);
	~TexturedVertexBuffer();

	UINT getSizeVertexList();

private:
	UINT m_size_vertex;
	UINT m_size_list;
private:
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
	RenderSystem* m_system = nullptr;
private:
	friend class DeviceContext;
};

