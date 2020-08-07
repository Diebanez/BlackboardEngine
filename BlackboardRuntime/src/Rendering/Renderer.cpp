//
// Created by diego on 24/07/2020.
//

#include "Renderer.h"

namespace BlackboardRuntime{

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera& camera) {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {

    }

    void Renderer::Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform){
        shader->Bind();
        shader->SetUniform("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        shader->SetUniform("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::Init() {
        RenderCommand::Init();
    }
}