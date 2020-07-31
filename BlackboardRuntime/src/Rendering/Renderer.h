 //
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_RENDERER_H
#define BLACKBOARDENGINE_RENDERER_H

#include "RenderCommand.h"
#include "RendererAPI.h"

 namespace BlackboardRuntime {
    class Renderer {
    public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

        inline static RendererAPI::API GetAPI(){return RendererAPI::GetAPI();}
    };
}


#endif //BLACKBOARDENGINE_RENDERER_H
