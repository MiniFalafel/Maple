#include "mppch.h"
#include "WindowsWindow.h"

#include "Maple/Events/KeyEvent.h"
#include "Maple/Events/MouseEvent.h"
#include "Maple/Events/ApplicationEvent.h"

#include "glad/glad.h"

#include "imgui.h"

namespace Maple {
	
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		MP_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProperties& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& props) {
		// Fill m_Data with data from the window properties
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		// Log beginning of window creation
		MP_CORE_INFO("Creating Window {0}, ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		// GLFW initialization
		if (!s_GLFWInitialized) {
			// Initialize GLFW and log if it fails to initialize
			int success = glfwInit();
			MP_CORE_ASSERT(success, "GLFW Failed to initialize!");
			// Set error callback
			glfwSetErrorCallback(GLFWErrorCallback);
			// Set s_GLFWInitialized to true
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_Window);
		// Load glad
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MP_CORE_ASSERT(success, "glad failed to initialize!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		setVsync(true);

		// Set GLFW callback functions
		// Size callback
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			// Get a reference to the Window's data
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
			// Set width and height
			data.Width = width; data.Height = height;

			// Get the event and dispatch it
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
		// Close callback
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			// Get a reference to the Window's data
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
			// Get and dispatch the window close event
			WindowCloseEvent event;
			data.EventCallback(event);

		});
		// Key callback
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			// Get a reference to the Window's data
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			// Action for each case
			switch (action) {
				case GLFW_PRESS: {
					// Get event and dispatch
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					// Get event and dispatch
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					// Get event and dispatch
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});
		// Char/Typing callback
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int c) {
			// Get a reference to the Window's data
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			KeyTypedEvent event(c);
			data.EventCallback(event);
		});
		// Mouse Button callback
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			// Get a reference to the Window's data
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			// Action for each case
			switch (action) {
				case GLFW_PRESS: {
					// Get event and dispatch
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					// Get event and dispatch
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});
		// Mouse position callback
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			// Get a reference to the Window's data
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			// Get event and dispatch
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
		// Mouse Scrolling
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			// Get a reference to the Window's data
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
			
			// Get event and dispatch
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown() {
		// Destroy the GLFW window
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		// Poll Events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::setVsync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.vSync = enabled;
	}

	bool WindowsWindow::isVsync() const {
		return m_Data.vSync;
	}
}