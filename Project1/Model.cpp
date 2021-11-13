#include "Model.h"

#include <iostream>
#include <Windows.h>
#include "GraphicsEngine.h"
#include "DeviceContext.h"

Model::Model(vertex vertices[], UINT size)
{
	m_vertices = vertices;
	m_listSize = size;
}

Model::Model(obj object)
{
	m_vertices = new vertex[object.faces.size() * 3];
	/*for (int i = 0; i < object.vertices.size(); i++)
	{
		m_vertices[i].position = m_vertices[i].position1 = object.vertices[i];
		m_vertices[i].color = m_vertices[i].color1 = { 0,1,0 };
	}
	m_listSize = object.vertices.size();*/

	for (int i = 0; i < object.faces.size() * 3; i+=3)
	{
		m_vertices[i].position = m_vertices[i].position1 = object.vertices[object.faces[i / 3].x-1];
		m_vertices[i+1].position = m_vertices[i+1].position1 = object.vertices[object.faces[i / 3].y-1];
		m_vertices[i+2].position = m_vertices[i+2].position1 = object.vertices[object.faces[i / 3].z-1];
		m_vertices[i].color = m_vertices[i].color1 = { 0,1,0 };
		m_vertices[i+1].color = m_vertices[i+1].color1 = { 0,1,0 };
		m_vertices[i+2].color = m_vertices[i+2].color1 = { 0,1,0 };
		
		m_vertices[i].color1 = { 1,0,0 };
		m_vertices[i+1].color1 = { 1,0,0 };
		m_vertices[i+2].color1 = { 1,0,0 };
	}
	m_listSize = object.faces.size() * 3;
}


Model::~Model()
{
}

void Model::vertexBufferLoad(void* shader_byte_code, size_t size_byte_shader)
{
	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	m_vb->load(m_vertices, sizeof(vertex), m_listSize, shader_byte_code, size_byte_shader);
}

void Model::Update()
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawPointList(m_vb->getSizeVertexList(), 0);
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawLineList(m_vb->getSizeVertexList(), 0);
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawLineStrip(m_vb->getSizeVertexList(), 0);
	
}
