#pragma once
#include "AGameObject.h"
#include "TexturedVertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Mesh.h"

class MeshObject :
    public AGameObject
{
public:
	MeshObject(std::string name, const wchar_t* meshPath, const wchar_t*  texPath);
	~MeshObject();

	void update(float deltaTime) override;
	void draw(int width, int height) override;

	void loadTexture(std::string filePath);

protected:
	TexturedVertexBufferPtr m_vb;
	IndexBufferPtr m_ib;
	ConstantBufferPtr m_cb;

	MeshPtr m_mesh = nullptr;
	TexturePtr m_texture = nullptr;

	float m_ticks = 0.0f;
	float m_deltaPos = 0.0f;
	float m_deltaTime = 0.0f;
	float m_speed = 10.0f;

	Matrix4x4 m_view;
	Matrix4x4 m_proj;
};

