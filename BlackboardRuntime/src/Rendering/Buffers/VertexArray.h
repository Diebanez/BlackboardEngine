#ifndef BLACKBOARDENGINE_VERTEXARRAY_H
#define BLACKBOARDENGINE_VERTEXARRAY_H

#include <Core/Core.h>
#include <memory>
#include <vector>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace BlackboardRuntime {
    class VertexArray{
        public:
            virtual ~VertexArray(){}

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

            virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
            virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

            virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
            virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

            static VertexArray* Create();
    };
}

#endif //BLACKBOARDENGINE_VERTEXARRAY_H