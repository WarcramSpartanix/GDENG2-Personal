#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class Cube : public AGameObject
{
public:
	Cube(std::string name);
	~Cube();
	
	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void setAnimSpeed(float speed);

	void setView(Matrix4x4 view);
	void setProj(Matrix4x4 proj);

protected:
	VertexBufferPtr m_vb;
	IndexBufferPtr m_ib;
	ConstantBufferPtr m_cb;

	float m_ticks = 0.0f;
	float m_deltaPos = 0.0f;
	float m_deltaTime = 0.0f;
	float m_speed = 10.0f;

	Matrix4x4 m_view;
	Matrix4x4 m_proj;
};

