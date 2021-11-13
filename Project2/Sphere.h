#pragma once
#include "Vector2D.h"
#include "AGameObject.h"

#include "TexturedVertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class Sphere :
    public AGameObject
{
private:
	struct Vertex {
		Vector3D position;
		Vector2D texCoord;
	};

public:
	Sphere(std::string name);
	~Sphere();

	void update(float deltaTime) override;
	void draw(int width, int height) override;

	void setView(Matrix4x4 view);
	void setProj(Matrix4x4 proj);

protected:
	TexturedVertexBufferPtr m_vb;
	IndexBufferPtr m_ib;
	ConstantBufferPtr m_cb;

	TexturePtr m_texture;

	float m_ticks = 0.0f;
	float m_deltaPos = 0.0f;
	float m_deltaTime = 0.0f;

	Matrix4x4 m_view;
	Matrix4x4 m_proj;
};

