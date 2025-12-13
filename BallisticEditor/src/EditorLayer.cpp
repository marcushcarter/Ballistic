#include "EditorLayer.h"

#include <imgui.h>
#include <imgui_impl_vulkan.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Platform/Vulkan/VulkanCommandBuffer.h"

namespace Ballistic {

	void EditorLayer::onAttach() {
		IMGUI_CHECKVERSION();
	    ImGui::CreateContext();

	    ImGuiIO& io = ImGui::GetIO();
	    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    	ImGui::StyleColorsDark();

    	switch (m_Window->getAPI()) {
	    	case WindowAPI::GLFW:
	    		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(m_Window->get()), true);
	    		break;

	    	default:
	    		break;
    	}

    	switch (m_Renderer->getAPI()) {
	    	case RendererAPI::OpenGL:
	    		ImGui_ImplOpenGL3_Init("#version 460");
	    		break;

	    	case RendererAPI::Vulkan:
	    		break;

	    	default:
	    		break;
    	}
	}

	void EditorLayer::onDetach() {

    	switch (m_Renderer->getAPI()) {
	    	case RendererAPI::OpenGL:
	    		ImGui_ImplOpenGL3_Shutdown();
	    		break;
	    	case RendererAPI::Vulkan:
	    		ImGui_ImplVulkan_Shutdown();
	    		break;
	    	default:
	    		break;
    	}

    	switch (m_Window->getAPI()) {
	    	case WindowAPI::GLFW:
	    		ImGui_ImplGlfw_Shutdown();
	    		break;
	    	default:
	    		break;
    	}

    	ImGui::DestroyContext();
	}

	void EditorLayer::onUpdate() {

    	switch (m_Renderer->getAPI()) {
	    	case RendererAPI::OpenGL:
	    		ImGui_ImplOpenGL3_NewFrame();
	    		break;
	    	case RendererAPI::Vulkan:
	    		ImGui_ImplVulkan_NewFrame();
	    		break;
	    	default:
	    		break;
    	}

    	switch (m_Window->getAPI()) {
	    	case WindowAPI::GLFW:
	    		ImGui_ImplGlfw_NewFrame();
	    		break;
	    	default:
	    		break;
    	}

    	ImGui::NewFrame();

    	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	    ImGui::SetNextWindowPos(viewport->Pos);
	    ImGui::SetNextWindowSize(viewport->Size);
	    ImGui::SetNextWindowViewport(viewport->ID);

	    ImGuiWindowFlags window_flags =
	        ImGuiWindowFlags_NoDocking |
	        ImGuiWindowFlags_NoTitleBar |
	        ImGuiWindowFlags_NoCollapse |
	        ImGuiWindowFlags_NoResize |
	        ImGuiWindowFlags_NoMove |
	        ImGuiWindowFlags_NoBringToFrontOnFocus |
	        ImGuiWindowFlags_NoNavFocus |
	        ImGuiWindowFlags_MenuBar;

	    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	    ImGui::Begin("dockspace", nullptr, window_flags);
	    
	    ImGuiID dockspace_id = ImGui::GetID("DockSpace");
	    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
	    
	    ImGui::PopStyleVar(3);
	    ImGui::End();

    	// ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    	ImGui::Begin("Editor Panel");
	    ImGui::Text("Hello from Ballistic EditorLayer!");
	    ImGui::End();

    	ImGui::Render();

    	switch (m_Renderer->getAPI()) {
        case RendererAPI::OpenGL:
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            break;
        case RendererAPI::Vulkan:
            break;
        default:
            break;
	    }

    	auto io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		    if (m_Window->getAPI() == WindowAPI::GLFW && m_Renderer->getAPI() == RendererAPI::OpenGL) {
		        GLFWwindow* backup = static_cast<GLFWwindow*>(m_Window->get());
		        ImGui::UpdatePlatformWindows();
		        ImGui::RenderPlatformWindowsDefault();
		        glfwMakeContextCurrent(backup);
		    }
		}


	}

	void EditorLayer::onEvent(void* ePtr) {
		Event* e = static_cast<Event*>(ePtr);
	}
}