#pragma once
#define NOMINMAX
#include <Windows.h>

class Window
{
public:
	Window();// Initialize Window
	~Window();//Release Window
	

	bool isRun();

	RECT getClientWindowRect();

	//Events
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

private:
	bool broadcast();

protected:
	HWND m_hwnd;
	bool m_is_run;
	bool m_is_init = false;
};

