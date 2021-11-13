#include "AppWindow.h"
#include <Windows.h>
#include "Vertex.h"
#include "ObjLoader.h"

__declspec(align(16))
struct constant
{
	float m_angle;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	GraphicsEngine::init();
	
	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();
	
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] =
	{
		
		{-0.5f, -0.5f, 0.0f,	-0.32f, -0.11f, 0.0f,		1, 0, 0,		0, 1, 0 },
		{-0.5f, 0.5f, 0.0f,	-0.11f, 0.78f, 0.0f,			0, 1, 0,		1, 1, 0},
		{0.5f, -0.5f, 0.0f,	0.75f, -0.73f, 0.0f,			0, 1, 1,		1, 0, 0},
		{0.5f, 0.5f, 0.0f,		0.88f, 0.77f, 0.0f,			1, 0, 1,		0, 0, 1}

		
	};

	/*vertex list[] =
	{
		{-0.5f, -0.5f, 0.0f,	-0.5f, -0.5f, 0.0f,		1, 0, 0,		0, 1, 0 },
		{-0.5f, -0.25f, 0.0f,	-0.5f, -0.25f, 0.0f,			0, 1, 0,		1, 1, 0},
		{-0.25f, -0.5f, 0.0f,		-0.25f, -0.5f, 0.0f,			1, 0, 1,		0, 0, 1},
		{-0.25f, -0.25f, 0.0f,	-0.25f, -0.25f, 0.0f,			0, 1, 1,		1, 0, 0}
	};*/
	vertex list2[] =
	{
		{0.5f, 0.5f, 0.0f,	0.5f, 0.5f, 0.0f,		1, 0, 0,		0, 1, 0 },
		{0.5f, 0.25f, 0.0f,	0.5f, 0.25f, 0.0f,			0, 1, 0,		1, 1, 0},
		{0.25f, 0.5f, 0.0f,		0.25f, 0.5f, 0.0f,			1, 0, 1,		0, 0, 1},
		{0.25f, 0.25f, 0.0f,	0.25f, 0.25f, 0.0f,			0, 1, 1,		1, 0, 0}
	};
	vertex list3[] =
	{
		{0.5f, -0.25f, 0.0f,	0.5f, -0.25f, 0.0f,		1, 0, 0,		0, 1, 0 },
		{0.5f, -0.5f, 0.0f,	0.5f, -0.5f, 0.0f,			0, 1, 0,		1, 1, 0},
		{0.25f, -0.25f, 0.0f,		0.25f, -0.25f, 0.0f,			1, 0, 1,		0, 0, 1},
		{0.25f, -0.5f, 0.0f,	0.25f, -0.5f, 0.0f,			0, 1, 1,		1, 0, 0}
	};

	std::string filename = "Obj/bunny.obj";
	obj* temp = new obj();
	ObjLoader::getInstance()->loadObjFromFile(filename, temp);
	
	//m_modelList.push_back(*new Model(*temp));
	m_modelList.push_back(*new Model(list, ARRAYSIZE(list)));
	//m_modelList.push_back(*new Model(list2, ARRAYSIZE(list2)));
	//m_modelList.push_back(*new Model(list3, ARRAYSIZE(list3)));
	

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	//Vertex Shader
	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	//m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	m_modelList[0].vertexBufferLoad(shader_byte_code, size_shader);
	/*m_modelList[1].vertexBufferLoad(shader_byte_code, size_shader);
	m_modelList[2].vertexBufferLoad(shader_byte_code, size_shader);*/
	GraphicsEngine::getInstance()->releaseCompiledShader();

	
	//Pixel Shader
	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	
	
	constant cc;
	cc.m_angle = 0;
	
	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(m_swap_chain, 0, 0, 1, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	m_angle += 1.57f * m_delta_time;
	constant cc;
	//cc.m_angle = 0;
	cc.m_angle = m_angle;
	
	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
	
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	/*GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);*/

	m_modelList[0].Update();
	/*m_modelList[1].Update();
	m_modelList[2].Update();*/

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::release();
}
