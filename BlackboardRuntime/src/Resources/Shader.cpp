//
// Created by diego on 24/07/2020.
//

#include "Shader.h"

namespace BlackboardRuntime{
    Shader* Shader::Create(std::vector<ShaderSource> src) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: {
                BB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            }
            case RendererAPI::OpenGL: {
                return new OpenGLShader(src);
            }

            BB_CORE_ASSERT(false, "Unknown Renderer API");
            return nullptr;
        }
    }
}