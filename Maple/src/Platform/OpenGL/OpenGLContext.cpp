#include "mppch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Maple {
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
		MP_CORE_ASSERT(m_WindowHandle, "Window Handle is null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MP_CORE_ASSERT(success, "glad failed to initialize!");

		MP_CORE_INFO("OpenGL Info:");
		MP_CORE_INFO("    Vendor:    {0}", glGetString(GL_VENDOR));
		MP_CORE_INFO("    Renderer:  {0}", glGetString(GL_RENDERER));
		MP_CORE_INFO("    Version:   {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}

}