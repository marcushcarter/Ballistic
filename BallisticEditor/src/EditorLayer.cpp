#include "EditorLayer.h"

#include <imgui.h>
#include <imgui_impl_vulkan.h>
#include <imgui_impl_glfw.h>

#include "Platform/Vulkan/VulkanCommandBuffer.h"

static void check_vk_result(VkResult err)
{
    if (err == 0)
        return;
    fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
    if (err < 0)
        abort();
}

namespace Ballistic {

	void EditorLayer::onAttach() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		    style.WindowRounding = 0.0f;
		    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForVulkan(m_Window->get(), true);
		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = m_Renderer->getVulkanInstance().get();
		init_info.PhysicalDevice = m_Renderer->getVulkanPhysicalDevice().get();
		init_info.Device = m_Renderer->getVulkanDevice().get();
		init_info.QueueFamily = m_Renderer->getVulkanDevice().getGraphicsQueueFamily();
		init_info.Queue = m_Renderer->getVulkanDevice().getGraphicsQueue();
		init_info.PipelineCache = VK_NULL_HANDLE;
		init_info.DescriptorPool = m_Renderer->getVulkanDescriptorPool().get();
		init_info.MinImageCount = m_Renderer->getVulkanSwapchain().getImages().size();
		init_info.ImageCount = m_Renderer->getVulkanSwapchain().getImages().size();
		// init_info.Allocator = g_Allocator;
		init_info.PipelineInfoMain.RenderPass = m_Renderer->getVulkanRenderPass().get();
		init_info.PipelineInfoMain.Subpass = 0;
		init_info.PipelineInfoMain.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
		init_info.CheckVkResultFn = check_vk_result;
		ImGui_ImplVulkan_Init(&init_info);

		// ImGui_ImplVulkan_CreateDeviceObjects();

		// VkCommandBuffer cmd = m_Renderer->getVulkanCommandBuffer().beginSingleTimeCommands();
		// ImGui_ImplVulkan_CreateFontsTexture(cmd);
		// m_Renderer->getVulkanCommandBuffer().endSingleTimeCommands(cmd, m_Renderer->getVulkanDevice().getGraphicsQueue());
		// ImGui_ImplVulkan_DestroyFontUploadObjects();
	}

	void EditorLayer::onDetach() {
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void EditorLayer::onUpdate() {
		// ImGui_ImplVulkan_NewFrame();
		// ImGui_ImplGlfw_NewFrame();
		// ImGui::NewFrame();

		// // // panels

		// ImGui::ShowDemoWindow();

		// ImGui::Render();
		// ImDrawData* draw_data = ImGui::GetDrawData();

		// VkCommandBuffer cmd = m_Renderer->getVulkanSwapchain().getCurrentCommandBuffer();
		// ImGui_ImplVulkan_RenderDrawData(draw_data, cmd);

		// if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		//     ImGui::UpdatePlatformWindows();
		//     ImGui::RenderPlatformWindowsDefault();
		// }
	}

	void EditorLayer::onEvent(void* ePtr) {
		Event* e = static_cast<Event*>(ePtr);
	}
}