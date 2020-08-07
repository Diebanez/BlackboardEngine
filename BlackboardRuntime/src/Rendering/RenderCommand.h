//
// Created by diego on 31/07/2020.
//

#ifndef BLACKBOARDENGINE_RENDERCOMMAND_H
#define BLACKBOARDENGINE_RENDERCOMMAND_H

#include "RendererAPI.h"

namespace BlackboardRuntime{
    class RenderCommand{
    public:
        inline static void Init(){
            m_RendererAPI->Init();
        }

        inline static void SetClearColor(const glm::vec4& color){
            m_RendererAPI->SetClearColor(color);
        }

        inline  static void Clear(){
            m_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const Ref<VertexArray>& vertexArray){
            m_RendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static RendererAPI* m_RendererAPI;
    };
}

#endif //BLACKBOARDENGINE_RENDERCOMMAND_H
