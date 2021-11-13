#pragma once
#include "InputListener.h"
#include <unordered_set>
#include "Point.h"
#include <vector>

class InputSystem
{
private:
	InputSystem();
	~InputSystem();
	static InputSystem* sharedInstance;

public:
	static void create();
	static void release();
	
	static InputSystem* getInstance();


	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void setCursorPosition(const Point& pos);
	void showCursor(bool show);

	void focus(bool isFocused);

private:
	std::vector<InputListener*> m_set_listeners;
	std::vector<InputListener*> m_standby_listeners;

	
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	Point m_old_mouse_pos;
	bool m_first_time = true;
};

