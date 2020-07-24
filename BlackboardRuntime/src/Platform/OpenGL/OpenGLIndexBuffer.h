//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_OPENGLINDEXBUFFER_H
#define BLACKBOARDENGINE_OPENGLINDEXBUFFER_H

#include <Rendering/Buffers/IndexBuffer.h>
#include <cstdint>

namespace BlackboardRuntime {
    class OpenGLIndexBuffer : public IndexBuffer{
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        void Bind() const override;
        void Unbind() const override;

        inline uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_Handle;
        uint32_t m_Count;
    };
}

#endif //BLACKBOARDENGINE_OPENGLINDEXBUFFER_H
