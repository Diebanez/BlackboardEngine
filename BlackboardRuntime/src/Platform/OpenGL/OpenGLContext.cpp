#include "OpenGLContext.h"

#include <Core/Core.h>
#include <Core/Log.h>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <gl/GL.h>

namespace BlackboardRuntime {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BB_CORE_ASSERT(status, "Failed to initialize Glad!");

		BB_CORE_INFO("Opengl Renderer");
		BB_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		BB_CORE_INFO("GPU: {0}", glGetString(GL_RENDERER));
		BB_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}