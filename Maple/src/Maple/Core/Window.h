#pragma once

#include "mppch.h"

#include "Maple/Core/Core.h"
#include "Maple/Events/Event.h"

namespace Maple {
	
	struct WindowProperties {

		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& title = "Maple Engine Window",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
		
	};

	class Window {

	public:
		using EventCallbackFn = std::function<void(Event&)>;

		// Virtual Destructor to be overriden
		virtual ~Window() {}

		// Overridable update function
		virtual void OnUpdate() = 0;

		// virtual Width and height getters
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Attributes and callback settings
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVsync(bool enabled) = 0;
		virtual bool isVsync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& props = WindowProperties());
	};

}