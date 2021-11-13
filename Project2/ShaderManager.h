#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include "Prerequisites.h"

class VertexShader;
class PixelShader;

namespace ShaderNames {
	const std::wstring  BASE_VERTEX_SHADER = L"VertexShader.hlsl";
	const std::wstring  TEXTURED_VERTEX_SHADER = L"TexturedVertexShader.hlsl";

	const std::wstring  BASE_PIXEL_SHADER = L"PixelShader.hlsl";
	const std::wstring  TEXTURED_PIXEL_SHADER = L"TexturedPixelShader.hlsl";
}

class ShaderManager
{
public:

	static ShaderManager* getInstance();

	void requestVertexShaderData(std::wstring  name, void** shaderByteCode, size_t* sizeShader);
	VertexShaderPtr getVertexShader(std::wstring  name);
	PixelShaderPtr getPixelShader(std::wstring  name);

private:
	ShaderManager();
	~ShaderManager();
	static ShaderManager* sharedInstance;

	std::unordered_map<std::wstring, VertexShaderPtr> m_vertex_shader_map;
	std::unordered_map<std::wstring, PixelShaderPtr> m_pixel_shader_map;
};
