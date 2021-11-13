#pragma warning(disable : 4996)
#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <locale>
#include <codecvt>
#include <iostream>

#include "GraphicsEngine.h"

Mesh::Mesh(const wchar_t* full_path) : Resource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(full_path);

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty())
		std::cout << "Mesh not created successfully" << std::endl;
	if (!res)
		std::cout << "Mesh not created successfully" << std::endl;

	if (shapes.size() > 1)
		std::cout << "Mesh has more than 1 shape" << std::endl;

	

	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;
		m_list_vertices.reserve(shapes[s].mesh.indices.size());
		m_list_indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];
				
				tinyobj::real_t tx = 0, ty = 0;

				if (attribs.texcoords.size() > 0)
				{
					tx = attribs.texcoords[index.texcoord_index * 2 + 0];
					ty = attribs.texcoords[index.texcoord_index * 2 + 1];
				}

				VertexMesh vert(Vector3D(vx, vy, vz), Vector2D(tx, ty));
				m_list_vertices.push_back(vert);
				m_list_indices.push_back((unsigned int)index_offset + v);
			}

			index_offset += num_face_verts;
		}
	}

}

Mesh::~Mesh()
{
}


