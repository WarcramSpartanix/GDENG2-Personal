#pragma once
#include "Vector3D.h"
#include "Vector2D.h"

class VertexMesh
{
public:
	VertexMesh() : m_position(), m_texcoord()
	{}
	VertexMesh(Vector3D pos, Vector2D tex) : m_position(pos), m_texcoord(tex)
	{}
	VertexMesh(const VertexMesh& vertexMesh) : m_position(vertexMesh.m_position), m_texcoord(vertexMesh.m_texcoord)
	{}

	~VertexMesh()
	{}

public:
	Vector3D m_position;
	Vector2D m_texcoord;
};