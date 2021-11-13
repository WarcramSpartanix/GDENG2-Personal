#include "Plane.h"

#include <iostream>

#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
#include "Vector3D.h"
#include "RenderSystem.h"
#include "ShaderManager.h"

Plane::Plane(std::string name) : AGameObject(name)
{
	type = PrimitiveType::PLANE;

	vertex vertex_list[] =
	{
		// FRONT	
		{Vector3D(-0.5f, 0.0f, -0.5f),	Vector3D(1, 0, 0),		Vector3D(1, 0, 0) },
		{Vector3D(-0.5f, 0.0f, 0.5f),	Vector3D(0, 1, 0),		Vector3D(0, 1, 0)},
		{Vector3D(0.5f, 0.0f, 0.5f),		Vector3D(0, 0, 1),		Vector3D(0, 0, 1)},
		{Vector3D(0.5f, 0.0f, -0.5f),	Vector3D(0, 1, 1),		Vector3D(0, 1, 1)},
	};

	void* shaderByteCode = NULL;
	size_t sizeShader = 0;
	ShaderManager::getInstance()->requestVertexShaderData(ShaderNames::BASE_VERTEX_SHADER, &shaderByteCode, &sizeShader);

	this->m_vb = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);

	unsigned int index_list[] =
	{
		0, 1, 2,
		2, 3, 0,
		2, 1, 0,
		0, 3, 2,
	};

	this->m_ib = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(index_list, ARRAYSIZE(index_list));

	
	constant cc = {};
	cc.m_time = 0.0f;
	this->m_cb = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

Plane::~Plane()
{
	AGameObject::~AGameObject();
}

void Plane::update(float deltaTime)
{

}

void Plane::draw(int width, int height)
{
	DeviceContextPtr deviceContext = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();

	deviceContext->setVertexShader(ShaderManager::getInstance()->getVertexShader(ShaderNames::BASE_VERTEX_SHADER));
	deviceContext->setPixelShader(ShaderManager::getInstance()->getPixelShader(ShaderNames::BASE_PIXEL_SHADER));

	constant cc = {};
	cc.m_time = 0;

	updateLocalMatrix();

	cc.m_world = this->localMatrix;
	//cc.m_view.setMatrix(m_view);
	cc.m_view.setMatrix(SceneCameraHandler::getInstance()->getCameraViewMatrix());

	//cc.m_proj.setOrthoLH
	//(
	//	width / 300.0f,
	//	height / 300.0f,
	//	/*-4.0f,
	//	4.0f*/
	//	0.1f,
	//	100.0f
	//);

	//cc.m_proj.setPerspectiveFovLH(1.57, ((float)width / ((float)height)), 0.1f, 100.0f);

	cc.m_proj = SceneCameraHandler::getInstance()->getProjectionMatrix();

	this->m_cb->update(deviceContext, &cc);
	deviceContext->setConstantBuffer(m_cb);

	deviceContext->setVertexBuffer(m_vb);
	deviceContext->setIndexBuffer(m_ib);
	deviceContext->drawIndexTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Plane::setAnimSpeed(float speed)
{
}
