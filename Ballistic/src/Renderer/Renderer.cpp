#include "Renderer.h"

namespace Ballistic {

	Renderer::~Renderer() {
	    Shutdown();
	}

	void Renderer::Init(std::shared_ptr<GLFWWindow> window) {
	    VulkanInstance::Config configInstance;
	    configInstance.enableValidation = true;
	    m_Instance = std::make_unique<VulkanInstance>(configInstance);

	    m_PhysicalDevice = std::make_unique<VulkanPhysicalDevice>(getVulkanInstance());

	    VulkanDevice::Config configDevice;
	    configDevice.extraExtensions = { "VK_KHR_swapchain" };
		configDevice.enabledFeatures.samplerAnisotropy = VK_TRUE;
		m_LogicalDevice = std::make_unique<VulkanDevice>(getVulkanPhysicalDevice(), configDevice);

		window->createVulkanSurface(getVulkanInstance().get());

	    VulkanSwapchain::Config configSwapchain;
	    configSwapchain.surface = window->getVkSurface();
		configSwapchain.imageCount = 2;
		configSwapchain.enableVSync = window->getProps().VSync;
		m_Swapchain = std::make_unique<VulkanSwapchain>(getVulkanDevice(), getVulkanPhysicalDevice(), configSwapchain);

		m_RenderPass = std::make_unique<VulkanRenderPass>(getVulkanDevice(), getVulkanSwapchain());

		m_Framebuffers = std::make_unique<VulkanFramebuffers>(getVulkanDevice(), getVulkanSwapchain(), getVulkanRenderPass());

		m_CommandBuffer = std::make_unique<VulkanCommandBuffer>(getVulkanDevice());

		// m_CommandBuffer->Begin();
	    // m_CommandBuffer->BeginRenderPass(getVulkanRenderPass(), getVulkanFramebuffers(), {1.0f, 0.0f, 0.0f, 1.0f}); // red
	    // m_CommandBuffer->EndRenderPass();
	    // m_CommandBuffer->End();

	    // m_CommandBuffer->Submit(getVulkanDevice().getGraphicsQueue(), getVulkanSwapchain());
	
		m_DescriptorPool = std::make_unique<VulkanDescriptorPool>(getVulkanDevice());
	}

	void Renderer::Shutdown() {
	}

}
