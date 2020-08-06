#include "OpenGLShader.h"

#include <glad/glad.h>
#include <Resources/Shader.h>
#include <Core/Log.h>
#include <glm/gtc/type_ptr.hpp>

namespace BlackboardRuntime {
	OpenGLShader::OpenGLShader(std::vector<ShaderSource> src) {
		std::vector<GLuint> shaders;

		for (auto shaderSourceData : src) {
			switch (shaderSourceData.Type)
			{
				case ShaderType::Vertex: {
					shaders.push_back(glCreateShader(GL_VERTEX_SHADER));
					break;
				}
				case ShaderType::Fragment: {
					shaders.push_back(glCreateShader(GL_FRAGMENT_SHADER));
					break;
				}
			}

			GLuint shader = shaders[shaders.size() - 1];

			const GLchar* shaderSource = shaderSourceData.Code.c_str();
			glShaderSource(shader, 1, &shaderSource, 0);
			glCompileShader(shader);
			
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				BB_CORE_ERROR("{0}", infoLog.data());
				BB_CORE_ASSERT(false, "Shader compilation failure");
				return;
			}
		}

		m_Handle = glCreateProgram();
		GLuint program = m_Handle;

		for (auto shader : shaders)
		{
			glAttachShader(program, shader);
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			for (auto shader : shaders)
			{
				glDeleteShader(shader);
			}

			BB_CORE_ERROR("{0}", infoLog.data());
			BB_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		for (auto shader : shaders)
		{
			glDetachShader(program, shader);
		}
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_Handle);
	}
	void OpenGLShader::Bind() {
		glUseProgram(m_Handle);
	}
	void OpenGLShader::Unbind() {
		glUseProgram(0);
	}

    void OpenGLShader::SetUniform(const std::string &name, int value) {
        GLint location = glGetUniformLocation(m_Handle, name.c_str());
        glUniform1i(location, value);

    }

    void OpenGLShader::SetUniform(const std::string &name, float value) {
        GLint location = glGetUniformLocation(m_Handle, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::SetUniform(const std::string &name, const glm::vec2 &value) {
        GLint location = glGetUniformLocation(m_Handle, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::SetUniform(const std::string &name, const glm::vec3 &value) {
        GLint location = glGetUniformLocation(m_Handle, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::SetUniform(const std::string &name, const glm::vec4 &value) {
        GLint location = glGetUniformLocation(m_Handle, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::SetUniform(const std::string &name, const glm::mat3 &matrix) {
        GLint location = glGetUniformLocation(m_Handle, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

    }

    void OpenGLShader::SetUniform(const std::string& name, const glm::mat4 &matrix) {
        GLint location = glGetUniformLocation(m_Handle, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}