#include "ImGuiLayer.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace ballistic
{
    ImGuiLayer::ImGuiLayer(const LayerContext& context, const std::string& name) 
        : ILayer(context, name) {}

    void ImGuiLayer::OnAttach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
	    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // ImFontConfig cfg;
		// cfg.PixelSnapH = true;
		// cfg.MergeMode = false;
		// io.Fonts->AddFontFromFileTTF((Config::RESOURCES_PATH / "Fonts/Noto_Sans/static/NotoSans-Regular.ttf").string().c_str(), 16.0f, &cfg);
		
		// cfg.MergeMode = true;
		// static const ImWchar icons_ranges[] = { 0xF000, 0xF8FF, 0 };
		// io.Fonts->AddFontFromFileTTF((Config::RESOURCES_PATH / "Fonts/fontawesome-free-6.6.0-desktop/Font Awesome 6 Free-Solid-900.otf").string().c_str(), 13.0f, &cfg, icons_ranges);
		
    	ImGui::StyleColorsDark();

        // ImGuiStyle& style = ImGui::GetStyle();
        // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        //     // style.WindowRounding = 0.0f;
        //     // style.TabRounding = 0.0f;
        //     // style.TabBarBorderSize = 0.0f;
        //     // style.GrabRounding = 2.0f;
        //     // style.ScrollbarRounding = 2.0f;
        //     // style.DockingSeparatorSize = 0.0f;
        //     // style.WindowBorderSize = 0.0f;
        // }

        // style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
        // style.WindowMenuButtonPosition = ImGuiDir_None;

        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(m_context.window->GetNativeWindow()), true);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void ImGuiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnUpdate(float deltaTime) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Demo Panel");
        ImGui::Text("Hello from ImGuiLayer!");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(IEvent& e) {
    }
    
} // namespace ballistic
