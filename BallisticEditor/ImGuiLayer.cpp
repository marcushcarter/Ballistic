#include "ImGuiLayer.h"

namespace ballistic
{
    ImGuiLayer::ImGuiLayer(const LayerContext& context, const std::string& name) 
        : ILayer(context, name) {}

    void ImGuiLayer::OnAttach() {

    }

    void ImGuiLayer::OnDetach() {

    }

    void ImGuiLayer::OnUpdate(float deltaTime) {
        // std::cout << "updates\n";
    }

    void ImGuiLayer::OnEvent(IEvent& e) {

    }
    
} // namespace ballistic
