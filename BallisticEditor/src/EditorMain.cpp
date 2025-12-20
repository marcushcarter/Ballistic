#include <Ballistic.h>
#include <Entry/BallisticEntrypoint.h>
#include "EditorLayer.h"

namespace Ballistic {

    class BallisticEditor : public Application {
    public:
        BallisticEditor() 
            : Application() {

            m_imguiContext = std::make_shared<ImGuiContext>(m_window);
			m_imguiContext->Init();

            m_layerStack->PushLayer(std::make_shared<EditorLayer>(GetAppContext(), m_imguiContext, std::string("EditorLayer")));
        }

        virtual void Shutdown() override {
            m_imguiContext->Shutdown();
            Application::Shutdown();
        }
        
        ~BallisticEditor() {
        }
    private:
        std::shared_ptr<ImGuiContext> m_imguiContext;
    };

    Application* CreateApplication(const std::filesystem::path& exeDir) {
        Config::Init(exeDir);
        return new BallisticEditor();
    }
}