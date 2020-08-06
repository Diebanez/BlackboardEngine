//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_SHADER_H
#define BLACKBOARDENGINE_SHADER_H

#include <cstdint>
#include <string>
#include <vector>
#include "Core/Core.h"
#include <glm/glm.hpp>

namespace BlackboardRuntime {
    enum class ShaderDataType{
        None = 0,
        Float = 1,
        Float2 = 2,
        Float3 = 3,
        Float4 = 4,
        Mat3 = 5,
        Mat4 = 6,
        Int = 7,
        Int2 = 8,
        Int3 = 9,
        Int4 = 10,
        Bool = 11
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type)
        {
            case ShaderDataType::Float: return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3: return 4 * 3 * 3;
            case ShaderDataType::Mat4: return 4 * 4 * 4;
            case ShaderDataType::Int: return 4;
            case ShaderDataType::Int2: return 4 * 2;
            case ShaderDataType::Int3: return 4 * 3;
            case ShaderDataType::Int4: return 4 * 4;
            case ShaderDataType::Bool: return 1;
        }

        BB_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    enum class ShaderType {
        Vertex = 0,
        Fragment = 1
    };

    struct ShaderSource{
        ShaderType Type;
        const std::string& Code;

        ShaderSource(ShaderType type, const std::string& src) : Type(type), Code(src){}
    };

    class Shader {
    public:
        virtual ~Shader(){}

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetUniform(const std::string& name, int value) = 0;
        virtual void SetUniform(const std::string& name, float value) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec2 &value) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec3 &value) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec4 &value) = 0;
        virtual void SetUniform(const std::string& name, const glm::mat3 &matrix) = 0;
        virtual void SetUniform(const std::string& name, const glm::mat4 &matrix) = 0;

        static Shader* Create(std::vector<ShaderSource> src);
    };
}

#endif //BLACKBOARDENGINE_SHADER_H
