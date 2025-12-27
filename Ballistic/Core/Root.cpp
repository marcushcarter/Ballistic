#include "Core/Root.h"
#include "Core/IApplication.h"

namespace ballistic
{
    Root::Root() = default;

    Root::~Root() {
        Shutdown();
    }
    
    void Root::SetApplication(std::unique_ptr<IApplication> app) {
        m_app = std::move(app);
    }

    bool Root::Init() {
        if (!m_app) return false;
        return m_app->Init();
    }

    void Root::Run() {
        if (!m_app) return;
        m_running = true;

        using clock = std::chrono::high_resolution_clock;
        auto lastTime = clock::now();

        while (m_running) {
            auto currentTime = clock::now();
            std::chrono::duration<float> elapsed = currentTime - lastTime;
            lastTime = currentTime;
            float deltaTime = elapsed.count();

            m_app->Update(deltaTime);
        }
    }

    void Root::Shutdown() {
        if (m_app) m_app->Shutdown();
        m_running = false;
    }
    
} // namespace ballistic
