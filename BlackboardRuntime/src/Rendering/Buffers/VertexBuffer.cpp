//
// Created by diego on 24/07/2020.
//

#include "VertexBuffer.h"
#include "Rendering/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace BlackboardRuntime{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None: {
                BB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            }
            case RendererAPI::OpenGL: { return new OpenGLVertexBuffer(vertices, size); }
        }

        BB_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;
    }
}