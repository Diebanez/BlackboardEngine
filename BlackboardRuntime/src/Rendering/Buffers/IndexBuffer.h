//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_INDEXBUFFER_H
#define BLACKBOARDENGINE_INDEXBUFFER_H


namespace BlackboardRuntime {
    class IndexBuffer {
    public:
        virtual ~IndexBuffer(){}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer* Create(uint32_t* indices, uint32_t count);
    };
}

#endif //BLACKBOARDENGINE_INDEXBUFFER_H
