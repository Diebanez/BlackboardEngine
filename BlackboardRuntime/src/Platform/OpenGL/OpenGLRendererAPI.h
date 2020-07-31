//
// Created by diego on 01/08/2020.
//

#ifndef BLACKBOARDENGINE_OPENGLRENDERERAPI_H
#define BLACKBOARDENGINE_OPENGLRENDERERAPI_H

#include <Rendering/RendererAPI.h>

namespace BlackboardRuntime{
class OpenGLRendererAPI : public RendererAPI{
public:
    void SetClearColor(const glm::vec4 &color) override;

    void Clear() override;

    void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
};
}

#endif //BLACKBOARDENGINE_OPENGLRENDERERAPI_H
