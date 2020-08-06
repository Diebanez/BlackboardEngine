//
// Created by diego on 31/07/2020.
//

#ifndef BLACKBOARDENGINE_RENDERERAPI_H
#define BLACKBOARDENGINE_RENDERERAPI_H

#include <glm/glm.hpp>
#include <Rendering/Buffers/VertexArray.h>

namespace BlackboardRuntime{
    class RendererAPI {
    public:
        enum class API {
            None = 0,
            OpenGL = 1
        };

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        inline static API GetAPI() {return m_API;}
    private:
        static API m_API;
    };
}

#endif //BLACKBOARDENGINE_RENDERERAPI_H
