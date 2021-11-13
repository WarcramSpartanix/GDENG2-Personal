#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	~Window();
	// Initialize Window
	bool init();
	bool broadcast();
	//Release Window
	bool release();
	bool isRun();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	//Events
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();

protected:
	HWND m_hwnd;
	bool m_is_run;
};

