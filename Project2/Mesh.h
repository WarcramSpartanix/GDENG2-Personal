#pragma once
#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>
#include "VertexMesh.h"

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();


	std::vector<VertexMesh> m_list_vertices;
	std::vector<unsigned int> m_list_indices;
private:

	friend class DeviceContext;

};

