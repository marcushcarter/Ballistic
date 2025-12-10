#pragma once

#include "lrpch.h"
#include "Core/Layers/LayerStack.h"

namespace Ballistic {

    class EditorLayer : public Layer {
    public:
        EditorLayer(std::shared_ptr<LayerStack> layerStack)
        : m_LayerStack(layerStack) {}

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(std::shared_ptr<IEvent> event) override;

    private:
        std::shared_ptr<LayerStack> m_LayerStack;
    };

}