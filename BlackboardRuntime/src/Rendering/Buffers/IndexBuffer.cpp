//
// Created by diego on 24/07/2020.
//

#include <cstdint>
#include <Rendering/Renderer.h>
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Core/Core.h"

namespace BlackboardRuntime {
    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: {
                BB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            }
            case RendererAPI::API::OpenGL: { return new OpenGLIndexBuffer(indices, size); }
        }

        BB_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;
    }
}
