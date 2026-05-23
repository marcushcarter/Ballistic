#include "EditorApplication.h"
#include "Images.h"

void EditorApplication::OnInit()
{
    LOG_DEBUG("Editor initialized");
    window.SetEmbeddedIcon(IMG_ICON_COMP_PNG);
    window.SetTitlebarColor(0.2f, 0.2f, 0.2f);
    
    renderer.CreateImGui(window.glfwWindow);

    // std::ifstream f(LAYOUT_FILE);
    // if (f.is_open()) {
    //     std::string data((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    //     ImGui::LoadIniSettingsFromMemory(data.c_str(), data.size());
    // }

    finalTextureID = ImGui_ImplVulkan_AddTexture(
        renderer.linearSampler.Get(),
        renderer.finalImage.GetView(),
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    );

    logoTextureID = ImGui_ImplVulkan_AddTexture(
        renderer.linearSampler.Get(),
        renderer.logoImage.GetView(),
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    );

    logoLongTextureID = ImGui_ImplVulkan_AddTexture(
        renderer.linearSampler.Get(),
        renderer.logoLongImage.GetView(),
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    );

    renderer.onSwapchainPass = [this](VkCommandBuffer cmd) {
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cmd);
    };
}

void EditorApplication::OnUpdate()
{
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    // if (ImGui::GetIO().WantSaveIniSettings) {
    //     size_t size = 0;
    //     const char* data = ImGui::SaveIniSettingsToMemory(&size);
    //     std::ofstream f(LAYOUT_FILE);
    //     if (f.is_open()) f.write(data, size);
    //     ImGui::GetIO().WantSaveIniSettings = false;
    // }

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("DockSpace", nullptr,
        ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoBackground
    );
    ImGui::PopStyleVar();
    ImGui::DockSpace(ImGui::GetID("MainDockSpace"), ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);
    ImGui::End();

    ImGui::Begin("Test Panel");
    ImGui::Text("Ballistic Engine");
    ImGui::Separator();
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Frame Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Begin("Viewport");
    ImVec2 size = ImGui::GetContentRegionAvail();
    ImGui::Image((ImTextureID)finalTextureID, size);
    size = ImVec2((float)renderer.logoImage.extent.width, (float)renderer.logoImage.extent.height);
    ImGui::Image((ImTextureID)logoTextureID, size);
    size = ImVec2((float)renderer.logoLongImage.extent.width, (float)renderer.logoLongImage.extent.height);
    ImGui::Image((ImTextureID)logoLongTextureID, size);
    ImGui::End();

    ImGui::Render();
}

void EditorApplication::OnShutdown()
{
    renderer.DestroyImGui();
    LOG_DEBUG("Editor shutdown");
}
