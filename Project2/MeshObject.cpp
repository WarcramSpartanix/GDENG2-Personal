#include "MeshObject.h"
#include "RenderSystem.h"
#include <iostream>

#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "VertexMesh.h"
#include "TextureManager.h"

MeshObject::MeshObject(std::string name, const wchar_t* meshPath, const wchar_t* texPath) : AGameObject(name)
{
	m_mesh = MeshManager::getInstance()->createMeshFromFile(meshPath);//(L"Obj\\teapot.obj");

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	ShaderManager::getInstance()->requestVertexShaderData(ShaderNames::TEXTURED_VERTEX_SHADER, &shaderByteCode, &sizeShader);

	this->m_vb = GraphicsEngine::getInstance()->getRenderSystem()->createTexturedVertexBuffer(&(m_mesh->m_list_vertices[0]), sizeof(VertexMesh), m_mesh->m_list_vertices.size(), shaderByteCode, sizeShader);

	this->m_ib = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(&(m_mesh->m_list_indices[0]), (UINT)m_mesh->m_list_indices.size());

	constant cc = {};
	cc.m_time = 0.0f;
	this->m_cb = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));

	if(texPath != nullptr)
		m_texture = TextureManager::getInstance()->createTextureFromFile(texPath);//(L"textures\\brick.png");
}

MeshObject::~MeshObject()
{
}

void MeshObject::update(float deltaTime)
{

}

void MeshObject::draw(int width, int height)
{
	DeviceContextPtr deviceContext = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();



	if (m_texture != nullptr)
	{
		deviceContext->setTexture(m_texture);
	}

	deviceContext->setVertexShader(ShaderManager::getInstance()->getVertexShader(ShaderNames::TEXTURED_VERTEX_SHADER));
	deviceContext->setPixelShader(ShaderManager::getInstance()->getPixelShader(ShaderNames::TEXTURED_PIXEL_SHADER));

	constant cc = {};
	cc.m_time = 0;

	updateLocalMatrix();

	cc.m_world = this->localMatrix;
	cc.m_view.setMatrix(SceneCameraHandler::getInstance()->getCameraViewMatrix());

	cc.m_proj = SceneCameraHandler::getInstance()->getProjectionMatrix();

	this->m_cb->update(deviceContext, &cc);

	deviceContext->setConstantBuffer(m_cb);
	deviceContext->setVertexBuffer(m_vb);
	deviceContext->setIndexBuffer(m_ib);
	deviceContext->drawIndexTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void MeshObject::loadTexture(std::string filePath)
{
}

