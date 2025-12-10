#include "RenderLayer.h"

#include "Core/Events/RenderEvents.h"

namespace Ballistic {

    void RenderLayer::OnAttach() {
        m_Renderer.Init();
    }

    void RenderLayer::OnDetach() {
    }

    void RenderLayer::OnUpdate() {
        // const auto& scene = m_ProjectManager->GetSceneManager()->GetOpenScene();
        const auto& assetPool = m_ProjectManager->GetAssetPool();
        std::shared_ptr<Image2D> image = m_Renderer.Render(assetPool.get());
        
        if (m_LayerStack)
            m_LayerStack->DispatchEvent(std::make_shared<FrameRenderedEvent>(image));
    }

}//