//
// Created by diego on 01/08/2020.
//

#ifndef BLACKBOARDENGINE_OPENGLRENDERERAPI_H
#define BLACKBOARDENGINE_OPENGLRENDERERAPI_H

#include <Rendering/RendererAPI.h>
#include <Core/Core.h>

namespace BlackboardRuntime{
class OpenGLRendererAPI : public RendererAPI{
public:
    virtual void Init() override ;
    virtual void SetClearColor(const glm::vec4 &color) override;
    virtual void Clear() override;
    virtual void DrawIndexed(const Ref<VertexArray> &vertexArray) override;
};
}

#endif //BLACKBOARDENGINE_OPENGLRENDERERAPI_H
