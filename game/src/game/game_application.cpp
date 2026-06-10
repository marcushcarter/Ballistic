#include <game/game_application.h>
#include <core/log.h>

void GameApplication::OnInit()
{
    window.onFramebufferResize = [this](uint32_t w, uint32_t h) {
        renderer.RequestWindowResize(w, h);
        renderer.RequestSceneResize(w, h);
    };

    onProjectLoadFailed = [this]() {
        Destroy();
    };

    // renderer.SetRenderPath(std::make_unique<GameRenderPath>(renderer));

    renderer.tempOnRender = [this](VkCommandBuffer cmd) {
        (void)cmd;
        // ViewportScissor(cmd, 0, 0, (float)renderer.swapchain.extent.width, (float)renderer.swapchain.extent.height);
        // renderer.blitPipeline.Bind(cmd);
        // struct { uint32_t srcIndex, samplerIndex; } pc;
        // pc.srcIndex = g.GetBindlessSampled(data.src);
        // pc.samplerIndex = renderer->linearSampler.bindlessSampler;
        // vkCmdPushConstants(cmd, renderer->globalPipelineLayout.Get(), VK_SHADER_STAGE_ALL, 0, 128, &pc);
        // vkCmdDraw(cmd, 3, 1, 0, 0);
    };
    
    // OpenProject(std::filesystem::current_path());
    OpenProject("D:/Ballistic Games/ballistic-engine/docs/samples/Test_Project");
    
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
    window.Show();
    // window.SetFullscreen(true);
}

void GameApplication::OnProjectClosed()
{

}
