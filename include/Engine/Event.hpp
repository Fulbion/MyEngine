#pragma once

#include <string>
#include <sstream>
#include <functional>

#include "Engine/Core.hpp"


namespace my
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		ApplicationTick, ApplicationUpdate, ApplicationRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		CategoryNone = 0,
		CategoryApplication = BIT(0),
		CategoryInput = BIT(1),
		CategoryKeyboard = BIT(2),
		CategoryMouse = BIT(3),
		CategoryMouseButton = BIT(4)
	};


	class MYENGINE_API Event
	{
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory i_category)
		{
			return getCategoryFlags() & i_category;
		}

	protected:
		bool m_handled = false;

	private:
		friend class EventDispatcher;
	};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }
	
	class MYENGINE_API EventDispatcher
	{
		template<typename T>
		using EventFunction = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& i_event) :
			m_event(i_event)
		{

		}

		template<typename T>
		bool dispatch(EventFunction<T> i_function)
		{
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.m_handled = i_function(*(T*)&m_event);
				return true;
			}

			return false;
		}

	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& i_os, const Event& i_event)
	{
		return i_os << i_event.toString();
	}

	class MYENGINE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint16_t i_width, uint16_t i_height) :
			m_width(i_width), m_height(i_height)
		{

		}

		inline uint16_t getWidth() const { return m_width; }
		inline uint16_t getHeight() const { return m_height; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: { m_width=" << m_width << ", m_height=" << m_height << " }";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(CategoryApplication)

	private:
		uint16_t m_width, m_height;
	};

	class MYENGINE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() { }

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(CategoryApplication)
	};

	class MYENGINE_API ApplicationTickEvent : public Event
	{
	public:
		ApplicationTickEvent() { }

		EVENT_CLASS_TYPE(ApplicationTick)
		EVENT_CLASS_CATEGORY(CategoryApplication)
	};

	class MYENGINE_API ApplicationUpdateEvent : public Event
	{
	public:
		ApplicationUpdateEvent() { }

		EVENT_CLASS_TYPE(ApplicationUpdate)
		EVENT_CLASS_CATEGORY(CategoryApplication)
	};

	class MYENGINE_API ApplicationRenderEvent : public Event
	{
	public:
		ApplicationRenderEvent() { }

		EVENT_CLASS_TYPE(ApplicationRender)
		EVENT_CLASS_CATEGORY(CategoryApplication)
	};

	class MYENGINE_API KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const { return m_keyCode; }
		EVENT_CLASS_CATEGORY(CategoryKeyboard | CategoryInput);

	protected:
		KeyEvent(int i_keyCode) :
			m_keyCode(i_keyCode)
		{

		}

		int m_keyCode;
	};

	class MYENGINE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int i_keyCode, int i_repeatCount) :
			KeyEvent(i_keyCode), m_repeatCount(i_repeatCount)
		{

		}

		inline int getRepeatCount() const { return m_repeatCount; }
		
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: { m_keyCode=" << m_keyCode << ", m_repeatCount=" << m_repeatCount << " }";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_repeatCount;
	};

	class MYENGINE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int i_keyCode) :
			KeyEvent(i_keyCode)
		{

		}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: { m_keyCode=" << m_keyCode << " }";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class MYENGINE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float i_x, const float i_y)
			: m_mouseX(i_x), m_mouseY(i_y) {}

		float getX() const { return m_mouseX; }
		float getY() const { return m_mouseY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: { m_mouseX=" << m_mouseX << ", m_mouseY=" << m_mouseY << " }";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(CategoryMouse | CategoryInput)
	
	private:
		float m_mouseX, m_mouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float i_offsetX, const float i_offsetY)
			: m_offsetX(i_offsetX), m_offsetY(i_offsetY) {}

		float getOffsetX() const { return m_offsetX; }
		float getOffsetY() const { return m_offsetY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: { m_offsetX=" << m_offsetX << ", m_offsetY=" << m_offsetY << " }";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(CategoryMouse | CategoryInput)

	private:
		float m_offsetX, m_offsetY;
	};

	class MouseButtonEvent : public Event
	{
	public:
		int GetMouseButton() const { return m_button; }
		EVENT_CLASS_CATEGORY(CategoryMouse | CategoryInput | CategoryMouseButton)

	protected:
		MouseButtonEvent(const int i_button)
			: m_button(i_button) {}

		int m_button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const int i_button)
			: MouseButtonEvent(i_button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: { m_button=" << m_button << " }";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const int i_button)
			: MouseButtonEvent(i_button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: { m_button=" << m_button << " }";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}