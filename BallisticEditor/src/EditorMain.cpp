#include <Ballistic.h>
#include <BallisticEntrypoint.h>

#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#define VULKAN_HPP_NO_CONSTRUCTORS
#define VULKAN_HPP_NO_SMART_HANDLE
#include <vulkan/vulkan.hpp>
#include "EditorLayer.h"

namespace Ballistic
{

    class BallisticEditor : public Application {
    public:
        BallisticEditor() : Application() {

            LayerContext context;
            context.layerStack = &m_LayerStack;
            context.window = m_Window.get();
            context.renderer = m_VkRenderer.get();

            m_LayerStack.pushLayer(std::make_shared<EditorLayer>(context, std::string("EditorLayer")));
        }

        virtual void Shutdown() override {
            Application::Shutdown();
        }
        
        ~BallisticEditor() {
        }
    };

    Application* CreateApplication() {
        return new BallisticEditor();
    }
}