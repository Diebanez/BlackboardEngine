#pragma once
#include <Resources/Shader.h>

namespace BlackboardRuntime{
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(std::vector<ShaderSource> src);
		virtual ~OpenGLShader();

		void Bind() override;
		void Unbind() override;

        void SetUniform(const std::string &name, int value) override;
        void SetUniform(const std::string &name, float value) override;
        void SetUniform(const std::string &name, const glm::vec2 &value) override;
        void SetUniform(const std::string &name, const glm::vec3 &value) override;
        void SetUniform(const std::string &name, const glm::vec4 &value) override;
        void SetUniform(const std::string &name, const glm::mat3 &matrix) override;
        void SetUniform(const std::string& name, const glm::mat4 &matrix) override;

    private:
		uint32_t m_Handle;
};
}