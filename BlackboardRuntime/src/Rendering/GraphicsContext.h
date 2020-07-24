//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_GRAPHICSCONTEXT_H
#define BLACKBOARDENGINE_GRAPHICSCONTEXT_H

namespace BlackboardRuntime{
public:
    virtual ~GraphicsContext() = default;
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
}

#endif //BLACKBOARDENGINE_GRAPHICSCONTEXT_H
