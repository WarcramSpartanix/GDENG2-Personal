#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class Plane : public AGameObject
{
public:
	Plane(std::string name);
	~Plane();

	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void setAnimSpeed(float speed);

private:
	VertexBufferPtr m_vb;
	IndexBufferPtr m_ib;
	ConstantBufferPtr m_cb;

	float m_ticks = 0.0f;
	float m_deltaPos = 0.0f;
	float m_deltaTime = 0.0f;
	float m_speed = 2.0f;
};

