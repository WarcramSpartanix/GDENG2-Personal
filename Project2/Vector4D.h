#pragma once
#pragma once

class Vector4D
{
public:
	Vector4D() : m_x(0), m_y(0), m_z(0), m_w(0)
	{}
	Vector4D(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w)
	{}
	Vector4D(const Vector4D& vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z), m_w(vector.m_w)
	{}

	~Vector4D()
	{}

	void cross(Vector4D& v1, Vector4D& v2, Vector4D& v3)
	{
		this->m_x = v1.m_y * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) + v1.m_w * (v2.m_y * v3.m_z - v2.m_z * v3.m_y);
		this->m_y = -(v1.m_x * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_x * v3.m_w - v3.m_x * v2.m_w) + v1.m_w * (v2.m_x * v3.m_z - v3.m_x * v2.m_z));
		this->m_z = v1.m_x * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) - v1.m_y * (v2.m_x * v3.m_w - v3.m_x * v2.m_w) + v1.m_w * (v2.m_x * v3.m_y - v3.m_x * v2.m_y);
		this->m_w = -(v1.m_x * (v2.m_y * v3.m_z - v3.m_y * v2.m_z) - v1.m_y * (v2.m_x * v3.m_z - v3.m_x * v2.m_z) + v1.m_z * (v2.m_x * v3.m_y - v3.m_x * v2.m_y));
	}
	
	void operator += (Vector4D target)
	{
		m_x += target.m_x;
		m_y += target.m_y;
		m_z += target.m_z;
	}

	float m_x, m_y, m_z, m_w;
private:



	friend class Matrix4x4;
};