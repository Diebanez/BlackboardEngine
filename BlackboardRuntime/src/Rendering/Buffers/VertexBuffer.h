//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_VERTEXBUFFER_H
#define BLACKBOARDENGINE_VERTEXBUFFER_H

namespace BlackboardRuntime {
    class VertexBuffer {
    public:
        virtual ~VertexBuffer();

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size);
    };
}


#endif //BLACKBOARDENGINE_VERTEXBUFFER_H
