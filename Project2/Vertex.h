#pragma once
#include <vector>
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"



struct int3
{
	int x, y, z;
};

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

struct vertex2D
{
	Vector3D position;
	Vector2D tex;
};

struct obj
{
	std::vector<vec3> vertices;
	std::vector<vec3> vertexNormal;
	std::vector<vec3> textureCoords;
	std::vector<int3> faces;
	
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_time;
};