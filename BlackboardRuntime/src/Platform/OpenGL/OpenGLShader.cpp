#include "OpenGLShader.h"

#include <glad/glad.h>
#include <Resources/Shader.h>
#include <Core/Log.h>

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
}