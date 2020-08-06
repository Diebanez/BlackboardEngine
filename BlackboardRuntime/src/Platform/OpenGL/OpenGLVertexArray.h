#ifndef BLACKBOARDENGINE_OPENGLVERTEXARRAY_H
#define BLACKBOARDENGINE_OPENGLVERTEXARRAY_H

#include <Rendering/Buffers/VertexArray.h>
#include <Core/Core.h>
#include <vector>
#include <glad/glad.h>
#include <Resources/Shader.h>

namespace BlackboardRuntime {
    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;

        const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const override {return  m_VertexBuffer;}
        const Ref<IndexBuffer> &GetIndexBuffer() const override{return  m_IndexBuffers;}

    private:
        uint32_t m_Handle;

        std::vector<Ref<VertexBuffer>> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffers;
    };
}

#endif //BLACKBOARDENGINE_OPENGLVERTEXARRAY_H