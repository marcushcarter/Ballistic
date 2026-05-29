#include "game_application.h"

void GameApplication::OnInit()
{
    window.onFramebufferResize = [this](uint32_t w, uint32_t h) {
        renderer.RequestWindowResize(w, h);
        renderer.RequestSceneResize(w, h);
    };

    onProjectLoadFailed = [this]() {
        Destroy();
    };
    
    renderer.onSwapchainPass = [this](VkCommandBuffer cmd) {
        VKViewportScissor(cmd, 0, 0, static_cast<float>(renderer.swapchain.extent.width), static_cast<float>(renderer.swapchain.extent.height));
        renderer.blitPipeline.Bind(cmd);
        renderer.blitPipeline.DescriptorSets(cmd, { renderer.finalImageInputSet.Get() });
        vkCmdDraw(cmd, 3, 1, 0, 0);
    };

    // OpenProject(std::filesystem::current_path());
    OpenProject("D:/Ballistic Games/ballistic-engine/docs/Test_Project");
    
    LOG_DEBUG("Game initialized");
}

void GameApplication::OnUpdate()
{

}

void GameApplication::OnShutdown()
{
    LOG_DEBUG("Game shutdown");
}

void GameApplication::OnProjectOpened(const std::filesystem::path& path)
{
    (void)path;
    window.SetTitle(project.name.c_str());
    window.SetFullscreen(true);
}

void GameApplication::OnProjectClosed()
{

}
