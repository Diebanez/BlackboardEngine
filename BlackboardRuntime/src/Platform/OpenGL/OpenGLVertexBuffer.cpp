//
// Created by diego on 24/07/2020.
//

#include "OpenGLVertexBuffer.h"

#include "glad/glad.h"

namespace BlackboardRuntime {
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
        glCreateBuffers(1, &m_Handle);
        glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &m_Handle);
    }

    void OpenGLVertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
    }

    void OpenGLVertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}