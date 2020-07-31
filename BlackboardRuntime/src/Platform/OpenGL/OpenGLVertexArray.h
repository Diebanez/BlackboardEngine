#ifndef BLACKBOARDENGINE_OPENGLVERTEXARRAY_H
#define BLACKBOARDENGINE_OPENGLVERTEXARRAY_H

#include <Rendering/Buffers/VertexArray.h>
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

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

        const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const override {return  m_VertexBuffer;}
        const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override{return  m_IndexBuffers;}

    private:
        uint32_t m_Handle;

        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffers;
    };
}

#endif //BLACKBOARDENGINE_OPENGLVERTEXARRAY_H