#pragma once

#include "lrpch.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Core/Events/IEvent.h"
#include "../../Renderer/Renderer.h"
#include "Project/ProjectManager.h"

namespace Ballistic {

    class RenderLayer : public Layer {
    public:
        RenderLayer(std::shared_ptr<LayerStack> layerStack, std::shared_ptr<ProjectManager> projectManager)
        : m_LayerStack(layerStack), m_ProjectManager(projectManager) {}

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;

    private:
        Renderer m_Renderer;

        std::shared_ptr<LayerStack> m_LayerStack;
        std::shared_ptr<ProjectManager> m_ProjectManager;
    };

}