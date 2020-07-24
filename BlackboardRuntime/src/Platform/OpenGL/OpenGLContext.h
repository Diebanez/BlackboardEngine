#pragma once
#include <Rendering/GraphicsContext.h>

struct GLFWwindow;

namespace BlackboardRuntime {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;

	};
}