//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_LAYER_H
#define BLACKBOARDENGINE_LAYER_H


#include <string>
#include <Events/Event.h>
#include <Rendering/Camera/OrthographicCamera.h>
#include "TimeStep.h"

namespace BlackboardRuntime {
    class Layer {
    public:
        Layer(const std::string &name = "Layer");

        virtual  ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(float time, TimeStep deltaTime) {}
        virtual void OnBeforeGuiRender() {}
        virtual void OnGuiRender() {}
        virtual void OnAfterGuiRender() {}
        virtual void OnEvent(Event& event){}

        inline const std::string &GetName() const { return m_DebugName; }

    private:
        std::string m_DebugName;
    };
}

#endif //BLACKBOARDENGINE_LAYER_H