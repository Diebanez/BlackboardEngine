#include "OpenGLShader.h"

#include <glad/glad.h>
#include <Core/Log.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

#ifdef BB_WINDOWS_PLATFORM
    #define EOL_TOKEN "\r\n"
#endif
#ifdef BB_LINUX_PLATFORM
    #define EOL_TOKEN "\n"
#endif

namespace BlackboardRuntime {
	OpenGLShader::OpenGLShader(std::vector<ShaderSource> src) {
	    Compile(src);
	}

    OpenGLShader::OpenGLShader(const std::string &path) {
	    std::string source = ReadFile(path);
	    auto shaderSources = PreProcess(source);
	    Compile(shaderSources);
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

    std::string OpenGLShader::ReadFile(const std::string &path) {
	    std::string result;
        std::ifstream in(path, std::ios::in | std::ios::binary);
	    if(in){
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            if(size != -1) {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
                in.close();
            }else{
                BB_CORE_ERROR("Could not read from gile '{0}'", path);
            }
	    }else{
	        BB_CORE_ERROR("Could not open file '{0}", path);
	    }

	    return result;
    }

    std::vector<ShaderSource> OpenGLShader::PreProcess(const std::string &source) {
	    std::vector<ShaderSource> result;

	    const char* typeToken = "#type";
	    size_t typeTokenLength = strlen(typeToken);
	    size_t pos = source.find(typeToken, 0);
	    while(pos != std::string::npos){
	        size_t eol = source.find_first_of(EOL_TOKEN, pos);
	        BB_CORE_ASSERT(eol != std::string::npos, "Syntax error");

	        size_t begin = pos + typeTokenLength + 1;
	        std::string type = source.substr(begin, eol - begin);
	        BB_CORE_ASSERT((int)ShaderDataTypeFromString(type), "Invalid shader type specified");

	        size_t nextLinePos = source.find_first_not_of(EOL_TOKEN, eol);
	        pos = source.find(typeToken, nextLinePos);
	        std::string sourceCode(pos == std::string::npos ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos));
	        result.push_back(ShaderSource(ShaderDataTypeFromString(type), sourceCode));
	    }
	    return result;
    }

    void OpenGLShader::Compile(const std::vector<ShaderSource> &src) {
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

    ShaderType OpenGLShader::ShaderDataTypeFromString(const std::string &value) {
        if(value == "vertex")
            return ShaderType::Vertex;
        if(value == "fragment")
            return ShaderType::Fragment;

        BB_CORE_ASSERT(false, "Unknown shader type!");
        return ShaderType::Unknown;
    }
}