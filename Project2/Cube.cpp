#include "Cube.h"
#include "RenderSystem.h"
#include <iostream>

#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
#include "ShaderManager.h"

Cube::Cube(std::string name) : AGameObject(name)
{
	type = PrimitiveType::CUBE;

	vertex vertex_list[] =
	{
		// FRONT	
		{Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(1, 0, 0),		Vector3D(0.2f, 0, 0) },
		{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(1, 1, 0),		Vector3D(0.2f, 0.2f, 0)},
		{Vector3D(0.5f, 0.5f, -0.5f),		Vector3D(1, 1, 0),		Vector3D(0.2f, 0.2f, 0)},
		{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1, 0, 0),		Vector3D(0.2f, 0, 0)},

		// BACK
		{Vector3D(0.5f, -0.5f, 0.5f),		Vector3D(0, 1, 0),		Vector3D(0, 0.2f, 0)},
		{Vector3D(0.5f, 0.5f, 0.5f),		Vector3D(0, 1, 1),		Vector3D(0, 0.2f, 0.2f)},
		{Vector3D(-0.5f, 0.5f, 0.5f),		Vector3D(1, 0, 1),		Vector3D(0.2f, 0, 0.2f)},
		{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(0, 1, 0),		Vector3D(0, 0.2f, 0)}
	};

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	ShaderManager::getInstance()->requestVertexShaderData(ShaderNames::BASE_VERTEX_SHADER, &shaderByteCode, &sizeShader);

	this->m_vb = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);

	unsigned int index_list[] =
	{
		// FRONT
		0, 1, 2,
		2, 3, 0,
		// BACK
		4, 5, 6,
		6, 7, 4,
		// TOP
		1, 6, 5,
		5, 2, 1,
		// BOTTOM
		7, 0, 3,
		3, 4, 7,
		// RIGHT
		3, 2, 5,
		5, 4, 3,
		// LEFT
		7, 6, 1,
		1, 0, 7
	};

	this->m_ib = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(index_list, ARRAYSIZE(index_list));

	constant cc = {};
	cc.m_time = 0.0f;
	this->m_cb = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
	
}

Cube::~Cube()
{
	AGameObject::~AGameObject();
}

void Cube::update(float deltaTime)
{
}

void Cube::draw(int width, int height)
{
	DeviceContextPtr deviceContext = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();

	deviceContext->setVertexShader(ShaderManager::getInstance()->getVertexShader(ShaderNames::BASE_VERTEX_SHADER));
	deviceContext->setPixelShader(ShaderManager::getInstance()->getPixelShader(ShaderNames::BASE_PIXEL_SHADER));

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

void Cube::setAnimSpeed(float speed)
{
	m_speed = speed;
}

void Cube::setView(Matrix4x4 view)
{
	m_view = view;
}

void Cube::setProj(Matrix4x4 proj)
{
	m_proj = proj;
}
