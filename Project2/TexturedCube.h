#pragma once
#include "Vector2D.h"
#include "AGameObject.h"

#include "TexturedVertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class TexturedCube : public AGameObject
{
private:
	struct Vertex {
		Vector3D position;
		Vector2D texCoord;
	};

public:
	TexturedCube(std::string name);
	~TexturedCube();

	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void setAnimSpeed(float speed);

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
	float m_speed = 10.0f;

	Matrix4x4 m_view;
	Matrix4x4 m_proj;
};

