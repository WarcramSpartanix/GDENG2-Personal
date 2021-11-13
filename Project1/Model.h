#pragma once
#include "Vertex.h"
#include <d3d11.h>
#include "VertexBuffer.h"

class Model
{
public:
	Model(vertex vertices[], UINT size);
	Model(obj object);
	~Model();

	vertex* m_vertices;
	UINT m_listSize;
	
	void vertexBufferLoad(void* shader_byte_code, size_t size_byte_shader);
	void Update();
	
private:
	VertexBuffer* m_vb;
};

