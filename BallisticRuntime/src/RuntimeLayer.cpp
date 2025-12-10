#include "RuntimeLayer.h"

namespace Ballistic {

    void RuntimeLayer::OnAttach() {
    }

    void RuntimeLayer::OnDetach() {
    }

    void RuntimeLayer::OnUpdate() {
    }

    void RuntimeLayer::OnEvent(std::shared_ptr<IEvent> event) {
        if (event->GetName() == std::string("FrameRenderedEvent")) {
            auto e = std::dynamic_pointer_cast<FrameRenderedEvent>(event);
            if (e) {
                // m_CurrentFrame = e->image;
                // std::cout << "Received frame!" << std::endl;
            }
        }
    }

}