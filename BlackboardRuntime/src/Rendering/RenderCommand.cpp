//
// Created by diego on 31/07/2020.
//

#include "RenderCommand.h"

#include <Platform/OpenGL/OpenGLRendererAPI.h>

namespace BlackboardRuntime{
    RendererAPI* RenderCommand::m_RendererAPI = new OpenGLRendererAPI;
}