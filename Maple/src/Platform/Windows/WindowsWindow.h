#pragma once

#include "Maple/Core/Window.h"
#include "Maple/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


namespace Maple {
	
	class WindowsWindow : public Window {
		
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Attributes and callback settings
		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		void setVsync(bool enabled) override;
		bool isVsync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; };

		// Windows creation
		static Window* Create(const WindowProperties& props = WindowProperties());

	private:
		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();

		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData {

			std::string Title;
			unsigned int Width, Height;
			bool vSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}