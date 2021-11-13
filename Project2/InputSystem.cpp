#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::sharedInstance = nullptr;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
	sharedInstance = nullptr;
}

void InputSystem::create()
{	
	if (sharedInstance)
	{
		throw std::exception("InputSystem already created");
	}
	sharedInstance = new InputSystem();
}

void InputSystem::release()
{
	if (!sharedInstance) return;
	delete sharedInstance;
}

InputSystem* InputSystem::getInstance()
{
	if (sharedInstance == nullptr)
		sharedInstance = new InputSystem();

	return sharedInstance;
}

void InputSystem::update()
{
	//Mouse Input
	
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	if(m_first_time)
	{
		m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		m_first_time = false;
	}
	
	if(current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y)
	{


		for (int i = 0; i < m_set_listeners.size(); i++)
		{
			m_set_listeners[i]->onMouseMove(Point(current_mouse_pos.x - m_old_mouse_pos.m_x, current_mouse_pos.y - m_old_mouse_pos.m_y));
		}
	}

	m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);




	
	// Keyboard Input
	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if (m_keys_state[i] & 0x80)
			{
				for (int j = 0; j < m_set_listeners.size(); j++)
				{
					if (i == VK_LBUTTON)	// Mouse Left
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							m_set_listeners[j]->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else if (i == VK_RBUTTON)	// Mouse Right
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							m_set_listeners[j]->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}

					//True Keyboard Input
					m_set_listeners[j]->onKeyDown(i);
				}
			}
			else // KEY IS UP
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					for (int j = 0; j < m_set_listeners.size(); j++)
					{
						if (i == VK_LBUTTON)	// Mouse Left
						{
							m_set_listeners[j]->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
						else if (i == VK_RBUTTON)	// Mouse Right
						{
							m_set_listeners[j]->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						}

						m_set_listeners[j]->onKeyUp(i);
					}
					
				}

			}

		}
		// store current keys state to old keys state buffer
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	m_set_listeners.push_back(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	for (int i = 0; i < m_set_listeners.size(); i++)
	{
		if(m_set_listeners[i] == listener)
		{
			m_set_listeners.erase(m_set_listeners.begin() + i);
		}
	}
	
}

void InputSystem::setCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

void InputSystem::focus(bool isFocused)
{
	if(isFocused)
	{
		for (int i = 0; i < m_standby_listeners.size(); i++)
		{
			m_set_listeners.push_back(m_standby_listeners[i]);
		}
		m_standby_listeners.clear();
	}
	else
	{
		for (int i = 0; i < m_set_listeners.size(); i++)
		{
			m_standby_listeners.push_back(m_set_listeners[i]);
		}
		m_set_listeners.clear();
	}
}
