//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_RENDERER_H
#define BLACKBOARDENGINE_RENDERER_H

namespace BlackboardRuntime {
    enum class RendererAPI{
        None = 0,
        OpenGL = 1
    };

    class Renderer {
    public:
        inline static RendererAPI GetAPI(){return m_RendererAPI;}

    private:
        static RendererAPI m_RendererAPI;
    };
}


#endif //BLACKBOARDENGINE_RENDERER_H
