//
// Created by diego on 24/07/2020.
//

#include "Shader.h"
#include <Platform/OpenGL/OpenGLVertexBuffer.h>
#include <Platform/OpenGL/OpenGLShader.h>
#include <Rendering/Renderer.h>

namespace BlackboardRuntime{
    Shader* Shader::Create(std::vector<ShaderSource> src) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: {
                BB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            }
            case RendererAPI::API::OpenGL: {
                return new OpenGLShader(src);
            }

            BB_CORE_ASSERT(false, "Unknown Renderer API");
            return nullptr;
        }
    }
}