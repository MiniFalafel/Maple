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
		
	#ifdef MP_ENABLE_ASSERTS
			int versionMajor, versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MAJOR_VERSION, &versionMinor);

			MP_CORE_ASSERT(versionMajor >= 4 && versionMinor >= 4, "Maple requires an OpenGL version of 4.4 or higher");
	#endif
	}


	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}

}