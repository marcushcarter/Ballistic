#include "VkRenderer.h"

namespace Ballistic {
	
	void VkRenderer::Init() {
		std::cout << "Vulkan Renderer Initialized" << std::endl;

		vk::ApplicationInfo appInfo{};
		appInfo.pApplicationName = "Ballistic Engine";
		appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
		appInfo.pEngineName = "Ballistic Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
		appInfo.apiVersion = VK_API_VERSION_1_3;

		vk::InstanceCreateInfo instanceInfo{};
		instanceInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		instanceInfo.ppEnabledExtensionNames = extensions.data();

		m_Instance = vk::createInstanceUnique(instanceInfo);

		m_Surface = m_Window->createVulkanSurface(*m_Instance);

		auto devices = m_Instance->enumeratePhysicalDevices();
		for (auto& device : devices) {
		    auto queueFamilies = device.getQueueFamilyProperties();
		    for (uint32_t i = 0; i < queueFamilies.size(); ++i) {
		        if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics) {
		            if (device.getSurfaceSupportKHR(i, *m_Surface)) {
		                m_PhysicalDevice = device;
		                m_GraphicsQueueFamilyIndex = i;
		                break;
		            }
		        }
		    }
		    if (m_PhysicalDevice) break;
		}

		if (!m_PhysicalDevice)
        	throw std::runtime_error("No suitable physical device found.");

		float queuePriority = 1.0f;
		vk::DeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.queueFamilyIndex = m_GraphicsQueueFamilyIndex;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		const char* deviceExtensions[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	    vk::DeviceCreateInfo deviceCreateInfo{};
	    deviceCreateInfo.queueCreateInfoCount = 1;
	    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
	    deviceCreateInfo.enabledExtensionCount = 1;
	    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions;

		m_Device = m_PhysicalDevice.createDeviceUnique(deviceCreateInfo);
		m_GraphicsQueue = m_Device->getQueue(m_GraphicsQueueFamilyIndex, 0);

		vk::SurfaceCapabilitiesKHR capabilities = m_PhysicalDevice.getSurfaceCapabilitiesKHR(*m_Surface);
		vk::Extent2D extent = capabilities.currentExtent;

		vk::SwapchainCreateInfoKHR swapchainInfo{};
		swapchainInfo.surface = *m_Surface;
		swapchainInfo.minImageCount = capabilities.minImageCount + 1;
		swapchainInfo.imageFormat = vk::Format::eB8G8R8A8Unorm;
		swapchainInfo.imageColorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;
		swapchainInfo.imageExtent = extent;
		swapchainInfo.imageArrayLayers = 1;
		swapchainInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;
		swapchainInfo.imageSharingMode = vk::SharingMode::eExclusive;
		swapchainInfo.preTransform = capabilities.currentTransform;
		swapchainInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
		swapchainInfo.presentMode = vk::PresentModeKHR::eFifo;
		swapchainInfo.clipped = VK_TRUE;

		m_Swapchain = m_Device->createSwapchainKHRUnique(swapchainInfo);
		m_SwapchainImages = m_Device->getSwapchainImagesKHR(*m_Swapchain);
		m_SwapchainImageFormat = vk::Format::eB8G8R8A8Unorm;
		m_SwapchainExtent = extent;

		m_SwapchainImageViews.resize(m_SwapchainImages.size());
	    for (size_t i = 0; i < m_SwapchainImages.size(); i++) {
	        vk::ImageViewCreateInfo viewInfo{};
	        viewInfo.image = m_SwapchainImages[i];
	        viewInfo.viewType = vk::ImageViewType::e2D;
	        viewInfo.format = m_SwapchainImageFormat;
	        viewInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
	        viewInfo.subresourceRange.baseMipLevel = 0;
	        viewInfo.subresourceRange.levelCount = 1;
	        viewInfo.subresourceRange.baseArrayLayer = 0;
	        viewInfo.subresourceRange.layerCount = 1;

	        m_SwapchainImageViews[i] = m_Device->createImageViewUnique(viewInfo);
	    }

		vk::AttachmentDescription colorAttachment{};
		colorAttachment.format = m_SwapchainImageFormat;
		colorAttachment.samples = vk::SampleCountFlagBits::e1;
		colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;
		colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;
		colorAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
		colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
		colorAttachment.initialLayout = vk::ImageLayout::eUndefined;
		colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;

		vk::AttachmentReference colorAttachmentRef{};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

		vk::SubpassDescription subpass{};
		subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		vk::RenderPassCreateInfo renderPassInfo{};
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &colorAttachment;
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;

		m_RenderPass = m_Device->createRenderPassUnique(renderPassInfo);

		m_Framebuffers.resize(m_SwapchainImages.size());
	    for (size_t i = 0; i < m_SwapchainImages.size(); i++) {
	        vk::FramebufferCreateInfo framebufferInfo{};
	        framebufferInfo.renderPass = *m_RenderPass;
	        framebufferInfo.attachmentCount = 1;
	        framebufferInfo.pAttachments = &(*m_SwapchainImageViews[i]);
	        framebufferInfo.width = m_SwapchainExtent.width;
	        framebufferInfo.height = m_SwapchainExtent.height;
	        framebufferInfo.layers = 1;

	        m_Framebuffers[i] = m_Device->createFramebufferUnique(framebufferInfo);
	    }

		vk::CommandPoolCreateInfo poolInfo{};
		poolInfo.queueFamilyIndex = m_GraphicsQueueFamilyIndex;
		poolInfo.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;

		m_CommandPool = m_Device->createCommandPoolUnique(poolInfo);
		m_CommandBuffers.resize(m_Framebuffers.size());

		vk::CommandBufferAllocateInfo allocInfo{};
		allocInfo.commandPool = *m_CommandPool;
		allocInfo.level = vk::CommandBufferLevel::ePrimary;
		allocInfo.commandBufferCount = static_cast<uint32_t>(m_CommandBuffers.size());

		auto rawBuffers = m_Device->allocateCommandBuffersUnique(allocInfo);
		for (size_t i = 0; i < m_CommandBuffers.size(); i++)
		    m_CommandBuffers[i] = std::move(rawBuffers[i]);

		for (size_t i = 0; i < m_CommandBuffers.size(); i++) {
		    vk::CommandBufferBeginInfo beginInfo{};
		    m_CommandBuffers[i]->begin(beginInfo);

		    vk::ClearValue clearColor = vk::ClearColorValue(std::array<float, 4>{1.0f, 0.0f, 0.0f, 1.0f});

		    vk::RenderPassBeginInfo renderPassInfo{};
		    renderPassInfo.renderPass = *m_RenderPass;
		    renderPassInfo.framebuffer = *m_Framebuffers[i];
		    renderPassInfo.renderArea.offset = vk::Offset2D{0, 0};
		    renderPassInfo.renderArea.extent = m_SwapchainExtent;
		    renderPassInfo.clearValueCount = 1;
		    renderPassInfo.pClearValues = &clearColor;

		    m_CommandBuffers[i]->beginRenderPass(renderPassInfo, vk::SubpassContents::eInline);
		    m_CommandBuffers[i]->endRenderPass();
		    m_CommandBuffers[i]->end();
		}
	}
	
	void VkRenderer::Shutdown() {
	    if (m_Device) m_Device->waitIdle();
	    m_Framebuffers.clear();
	    m_SwapchainImageViews.clear();
	    m_CommandBuffers.clear();
	    m_CommandPool.reset();
	    m_RenderPass.reset();
	    m_Swapchain.reset();
	    m_Surface.reset();
	    m_Device.reset();
	    m_Instance.reset();
	}

	void VkRenderer::Render() {
		vk::SemaphoreCreateInfo semaphoreInfo{};
	    auto imageAvailable = m_Device->createSemaphoreUnique(semaphoreInfo);
	    auto renderFinished = m_Device->createSemaphoreUnique(semaphoreInfo);

	    uint32_t imageIndex = m_Device->acquireNextImageKHR(*m_Swapchain, UINT64_MAX, *imageAvailable, nullptr).value;

	    vk::SubmitInfo submitInfo{};
	    vk::Semaphore waitSemaphores[] = { *imageAvailable };
	    vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };
	    submitInfo.waitSemaphoreCount = 1;
	    submitInfo.pWaitSemaphores = waitSemaphores;
	    submitInfo.pWaitDstStageMask = waitStages;
	    submitInfo.commandBufferCount = 1;
	    submitInfo.pCommandBuffers = &(*m_CommandBuffers[imageIndex]);
	    vk::Semaphore signalSemaphores[] = { *renderFinished };
	    submitInfo.signalSemaphoreCount = 1;
	    submitInfo.pSignalSemaphores = signalSemaphores;

	    m_GraphicsQueue.submit(submitInfo, nullptr);

	    vk::PresentInfoKHR presentInfo{};
	    presentInfo.waitSemaphoreCount = 1;
	    presentInfo.pWaitSemaphores = signalSemaphores;
	    vk::SwapchainKHR swapChains[] = { *m_Swapchain };
	    presentInfo.swapchainCount = 1;
	    presentInfo.pSwapchains = swapChains;
	    presentInfo.pImageIndices = &imageIndex;

	    vk::Result presentResult = m_GraphicsQueue.presentKHR(presentInfo);
		if (presentResult != vk::Result::eSuccess && presentResult != vk::Result::eSuboptimalKHR)
		    throw std::runtime_error("Failed to present swapchain image");

	    m_Device->waitIdle();
	}
}