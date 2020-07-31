//
// Created by diego on 24/07/2020.
//

#include "Renderer.h"

namespace BlackboardRuntime{

    void Renderer::BeginScene() {

    }

    void Renderer::EndScene() {

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray) {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}