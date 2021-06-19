#pragma once

#include "Event.h"

namespace Maple {
	
	class MAPLE_API KeyEvent : public Event {
		
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keyCode) : m_KeyCode(keyCode) {}

		int m_KeyCode;
	};

	class MAPLE_API KeyPressedEvent : public KeyEvent {
		int m_repeatCount;
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_repeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_repeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_repeatCount << "repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

}