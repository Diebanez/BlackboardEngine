//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_OPENGLVERTEXBUFFER_H
#define BLACKBOARDENGINE_OPENGLVERTEXBUFFER_H

#include <Rendering/Buffers/BufferLayout.h>
#include <Rendering/Buffers/VertexBuffer.h>
#include <cstdint>

namespace BlackboardRuntime {
    class OpenGLVertexBuffer : public VertexBuffer{
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;

        virtual const BufferLayout& GetLayout() const override { return m_Layout; }
        virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

    private:
        uint32_t m_Handle;
        BufferLayout m_Layout;
    };
}


#endif //BLACKBOARDENGINE_OPENGLVERTEXBUFFER_H
