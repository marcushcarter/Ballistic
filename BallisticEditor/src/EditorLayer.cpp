#include "EditorLayer.h"

namespace Ballistic {

    void EditorLayer::OnAttach() {
    }

    void EditorLayer::OnDetach() {
    }

    void EditorLayer::OnUpdate() {
    }

    void EditorLayer::OnEvent(std::shared_ptr<IEvent> event) {
        // if (event->GetName() == std::string("FrameRenderedEvent")) {
        //     auto e = std::dynamic_pointer_cast<FrameRenderedEvent>(event);
        //     if (e) {
        //         auto image = e->image;
        //         std::cout << "Received frame!" << std::endl;
        //     }
        // }
    }

}