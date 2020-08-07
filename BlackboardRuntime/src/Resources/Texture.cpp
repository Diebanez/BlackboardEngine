#pragma once

#include "Texture.h"
#include <Platform/OpenGL/OpenGLTexture.h>
#include <Rendering/Renderer.h>
namespace BlackboardRuntime{
    Ref<Texture2D> Texture2D::Create(const std::string& path){
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: BB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
        }

        BB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}