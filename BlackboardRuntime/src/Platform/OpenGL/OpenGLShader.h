#pragma once
#include <Resources/Shader.h>

namespace BlackboardRuntime{
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(std::vector<ShaderSource> src);
		virtual ~OpenGLShader();

		void Bind() override;
		void Unbind() override;

	private:
		uint32_t m_Handle;
};
}