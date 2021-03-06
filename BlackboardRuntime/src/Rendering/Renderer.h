 //
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_RENDERER_H
#define BLACKBOARDENGINE_RENDERER_H

#include <Resources/Shader.h>
#include "RenderCommand.h"
#include "RendererAPI.h"
#include "Camera/OrthographicCamera.h"

 namespace BlackboardRuntime {
    class Renderer {
    public:
        static void Init();

        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform = glm::mat4(1.0f));

        inline static RendererAPI::API GetAPI(){return RendererAPI::GetAPI();}
    private:
        struct SceneData{
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;

    };
}


#endif //BLACKBOARDENGINE_RENDERER_H
