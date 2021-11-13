#include "Window.h"
#include "EngineTime.h"
#include "UIManager.h"
#include <exception>

Window* window = NULL;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
        return true;

    switch (msg)
    {
    case WM_CREATE:
    {
        // Event fired when the window is created

       /* window->setHWND(hwnd);
        window->onCreate();*/
        break;
    }
    case WM_DESTROY:
    {
        // Event fired when the window is destroyed
        window->onDestroy();
        ::PostQuitMessage(0);
        break;
    }
    case WM_SETFOCUS:
    {
        // Event fired when the window get focus
        window->onFocus();
        if (window)
            window->onFocus();
        break;
    }
    case WM_KILLFOCUS:
    {
        // Event fired when the window loses focus
        window->onKillFocus();
        break;
    }


    default:
        return ::DefWindowProc(hwnd, msg, wparam, lparam);
        break;
    }

    return NULL;
}

Window::Window()
{
    WNDCLASSEX wc;
    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = NULL;
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.style = NULL;
    wc.lpfnWndProc = &WndProc;

    if (!::RegisterClassEx(&wc))
        throw std::exception("Window not created successfully");

    if (!window)
        window = this;

    m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        UIManager::WINDOW_WIDTH, UIManager::WINDOW_HEIGHT, NULL, NULL, NULL, NULL);

    if (!m_hwnd)
        throw std::exception("Window not created successfully");

    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);



    m_is_run = true;

    EngineTime::initialize();
}

Window::~Window()
{
}



bool Window::broadcast()
{
    EngineTime::LogFrameStart();
	
    MSG msg;

    if (!this->m_is_init)
    {
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
        window->onCreate();

        this->m_is_init = true;
    }

    window->onUpdate();

    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


    Sleep(0);

    EngineTime::LogFrameEnd();
	
    return true;
}

bool Window::isRun()
{
    if(m_is_run)
        broadcast();
    return m_is_run;
}

RECT Window::getClientWindowRect()
{
    RECT rc;
    ::GetClientRect(this->m_hwnd, &rc);
    return rc;
}

void Window::onDestroy()
{
    m_is_run = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}
