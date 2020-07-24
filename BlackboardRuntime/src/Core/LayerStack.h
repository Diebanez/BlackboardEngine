//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_LAYERSTACK_H
#define BLACKBOARDENGINE_LAYERSTACK_H


#include <vector>
#include "Layer.h"

namespace BlackboardRuntime {
    class LayerStack {
    public:
        LayerStack();

        ~LayerStack();

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);
        void PopLayer(Layer *layer);
        void PopOverlay(Layer *layer);

        std::vector<Layer *>::iterator begin() { return m_Layers.begin(); }

        std::vector<Layer *>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Layer *> m_Layers;
        unsigned int mLayerInsertIndex = 0;
    };
}

#endif //BLACKBOARDENGINE_LAYERSTACK_H
