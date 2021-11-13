#pragma once
#include <vector>
struct vec3
{
	float x, y, z;
};

struct int3
{
	int x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

struct obj
{
	std::vector<vec3> vertices;
	std::vector<vec3> vertexNormal;
	std::vector<vec3> textureCoords;
	std::vector<int3> faces;
	
};