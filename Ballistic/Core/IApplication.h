#pragma once
#include "bepch.h"

namespace ballistic
{
    class Window;
    class LayerStack;

    struct LayerContext {
        LayerStack* layerStack = nullptr;
        Window* window = nullptr;
    };

    class IApplication
    {
    public:
        IApplication();        
        virtual ~IApplication() = default;

        bool Init();
        void Update(float deltaTime);
        void Shutdown();

        void SetExeDirectory(const std::filesystem::path& path) { m_exeDir = path; }
        const std::filesystem::path& GetExeDirectory() const { return m_exeDir; }
        
        std::shared_ptr<LayerStack> GetLayerStack() { return m_layerStack; }
    
    protected:
        virtual bool OnInit() = 0;
        virtual void OnUpdate(float deltaTime) = 0;
        virtual void OnShutdown() = 0;
        
        LayerContext CreateLayerContext() {
            LayerContext ctx;
            ctx.layerStack = m_layerStack.get();
            ctx.window = m_window.get();
            return ctx;
        }

        std::shared_ptr<LayerStack> m_layerStack;
        std::unique_ptr<Window> m_window;

    private:
        std::filesystem::path m_exeDir;
    };
    
} // namespace ballistic

