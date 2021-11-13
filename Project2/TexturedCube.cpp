#include "TexturedCube.h"
#include "RenderSystem.h"
#include <iostream>

#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
#include "ShaderManager.h"
#include "TextureManager.h"

TexturedCube::TexturedCube(std::string name): AGameObject(name)
{
	type = PrimitiveType::CUBE;

	Vector3D position_list[] =
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};



	vertex2D vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] },


		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },


		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }


	};

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	ShaderManager::getInstance()->requestVertexShaderData(ShaderNames::TEXTURED_VERTEX_SHADER, &shaderByteCode, &sizeShader);

	this->m_vb = GraphicsEngine::getInstance()->getRenderSystem()->createTexturedVertexBuffer(vertex_list, sizeof(vertex2D), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};

	this->m_ib = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(index_list, ARRAYSIZE(index_list));

	constant cc = {};
	cc.m_time = 0.0f;
	this->m_cb = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));

	m_texture = TextureManager::getInstance()->createTextureFromFile(L"textures\\wood.jpg");

}

TexturedCube::~TexturedCube()
{
}

void TexturedCube::update(float deltaTime)
{
}

void TexturedCube::draw(int width, int height)
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

void TexturedCube::setAnimSpeed(float speed)
{
	m_speed = speed;
}

void TexturedCube::setView(Matrix4x4 view)
{
	m_view = view;
}

void TexturedCube::setProj(Matrix4x4 proj)
{
	m_proj = proj;
}
