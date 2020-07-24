//
// Created by diego on 24/07/2020.
//

#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>

namespace BlackboardRuntime {
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)  : m_Count(count){
        glCreateBuffers(1, &m_Handle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &m_Handle);
    }

    void OpenGLIndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
    }

    void OpenGLIndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}