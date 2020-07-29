#include "VertexArray.h"
#include <Rendering/Renderer.h>
#include <Core/Core.h>
#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace BlackboardRuntime{
    VertexArray* VertexArray::Create(){
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None: BB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL: return new OpenGLVertexArray();
        }

        BB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}