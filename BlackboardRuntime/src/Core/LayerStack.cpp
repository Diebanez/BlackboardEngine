//
// Created by diego on 24/07/2020.
//

#include "LayerStack.h"

namespace BlackboardRuntime {
    LayerStack::LayerStack() {
    }

    LayerStack::~LayerStack() {
        for (Layer* layer : m_Layers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer) {
        m_Layers.emplace(m_Layers.begin() + mLayerInsertIndex , layer);
        mLayerInsertIndex ++;
        layer->OnAttach();
    }

    void LayerStack::PushOverlay(Layer* layer) {
        m_Layers.emplace_back(layer);
        layer->OnAttach();
    }

    void LayerStack::PopLayer(Layer* layer) {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if (it != m_Layers.end()) {
            layer->OnDetach();
            m_Layers.erase(it);
            mLayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* layer) {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if (it != m_Layers.end()) {
            layer->OnDetach();
            m_Layers.erase(it);
        }
    }
}
