#pragma once
#include <Resources/Shader.h>

namespace BlackboardRuntime{
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(std::vector<ShaderSource> src);
		virtual ~OpenGLShader();

		void Bind() override;
		void Unbind() override;

        void OpenGLShader::SetUniform(const std::string& name, const glm::mat4 &matrix) override;

    private:
		uint32_t m_Handle;
};
}