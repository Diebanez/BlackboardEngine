#include "VertexArray.h"
#include "Renderer.h"
#include "Core.h"

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