#include "ShaderManager.h"
#include "GraphicsEngine.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "RenderSystem.h"

ShaderManager* ShaderManager::sharedInstance = NULL;

ShaderManager::ShaderManager()
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	void* shader_byte_code = NULL;
	size_t size_byte_shader = 0;

	graphicsEngine->getRenderSystem()->compileVertexShader(ShaderNames::BASE_VERTEX_SHADER.c_str(), "vsmain", &shader_byte_code, &size_byte_shader);
	m_vertex_shader_map[ShaderNames::BASE_VERTEX_SHADER] = graphicsEngine->getRenderSystem()->createVertexShader(shader_byte_code, size_byte_shader);

	graphicsEngine->getRenderSystem()->compilePixelShader(ShaderNames::BASE_PIXEL_SHADER.c_str(), "psmain", &shader_byte_code, &size_byte_shader);
	m_pixel_shader_map[ShaderNames::BASE_PIXEL_SHADER] = graphicsEngine->getRenderSystem()->createPixelShader(shader_byte_code, size_byte_shader);

	graphicsEngine->getRenderSystem()->compileVertexShader(ShaderNames::TEXTURED_VERTEX_SHADER.c_str(), "vsmain", &shader_byte_code, &size_byte_shader);
	m_vertex_shader_map[ShaderNames::TEXTURED_VERTEX_SHADER] = graphicsEngine->getRenderSystem()->createVertexShader(shader_byte_code, size_byte_shader);

	graphicsEngine->getRenderSystem()->compilePixelShader(ShaderNames::TEXTURED_PIXEL_SHADER.c_str(), "psmain", &shader_byte_code, &size_byte_shader);
	m_pixel_shader_map[ShaderNames::TEXTURED_PIXEL_SHADER] = graphicsEngine->getRenderSystem()->createPixelShader(shader_byte_code, size_byte_shader);

}

ShaderManager::~ShaderManager()
{
	m_vertex_shader_map.clear();
	m_pixel_shader_map.clear();
}

ShaderManager* ShaderManager::getInstance()
{
	if (sharedInstance == nullptr)
		sharedInstance = new ShaderManager();
	return sharedInstance;
}

void ShaderManager::requestVertexShaderData(std::wstring name, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
	graphEngine->getRenderSystem()->compileVertexShader(name.c_str(), "vsmain", shaderByteCode, sizeShader);
}

VertexShaderPtr ShaderManager::getVertexShader(std::wstring name)
{
	if (m_vertex_shader_map[name] == NULL) {
		std::cout << name.c_str() << " not found" << std::endl;
	}
	return m_vertex_shader_map[name];
}

PixelShaderPtr ShaderManager::getPixelShader(std::wstring name)
{
	if (m_pixel_shader_map[name] == NULL) {
		std::cout << name.c_str() << " not found" << std::endl;
	}
	return m_pixel_shader_map[name];
}