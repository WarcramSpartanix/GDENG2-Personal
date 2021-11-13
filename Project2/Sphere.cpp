#include "Sphere.h"
#include "RenderSystem.h"
#include <iostream>

#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
#include "ShaderManager.h"
#include "TextureManager.h"

Sphere::Sphere(std::string name) : AGameObject(name)
{
	type = PrimitiveType::SPHERE;

}

Sphere::~Sphere()
{
}

void Sphere::update(float deltaTime)
{
}

void Sphere::draw(int width, int height)
{
	DeviceContextPtr deviceContext = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();

	deviceContext->setTexture(m_texture);
	deviceContext->setVertexShader(ShaderManager::getInstance()->getVertexShader(ShaderNames::TEXTURED_VERTEX_SHADER));
	deviceContext->setPixelShader(ShaderManager::getInstance()->getPixelShader(ShaderNames::TEXTURED_PIXEL_SHADER));

	constant cc = {};
	cc.m_time = 0;

	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setTranslation(getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(getLocalScale());

	Vector3D rotation = getLocalRotation();
	Matrix4x4 zMatrix; zMatrix.setIdentity(); zMatrix.setRotationZ(rotation.getValues().z);
	Matrix4x4 yMatrix; yMatrix.setIdentity(); yMatrix.setRotationY(rotation.getValues().y);
	Matrix4x4 xMatrix; xMatrix.setIdentity(); xMatrix.setRotationX(rotation.getValues().x);
	Matrix4x4 rotationMatrix; rotationMatrix.setIdentity();
	rotationMatrix = rotationMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotationMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);



	cc.m_world = allMatrix;
	cc.m_view.setMatrix(SceneCameraHandler::getInstance()->getCameraViewMatrix());

	cc.m_proj = SceneCameraHandler::getInstance()->getProjectionMatrix();

	this->m_cb->update(deviceContext, &cc);

	deviceContext->setConstantBuffer(m_cb);
	deviceContext->setVertexBuffer(m_vb);
	deviceContext->setIndexBuffer(m_ib);
	deviceContext->drawIndexTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Sphere::setView(Matrix4x4 view)
{
	m_view = view;
}

void Sphere::setProj(Matrix4x4 proj)
{
	m_proj = proj;
}