#pragma once

#include "bepch.h"
#include "Platform/GLFW/GLFWWindow.h"
#include "Platform/Vulkan/VulkanInstance.h"
#include "Platform/Vulkan/VulkanPhysicalDevice.h"
#include "Platform/Vulkan/VulkanDevice.h"
#include "Platform/Vulkan/VulkanSwapchain.h"
#include "Platform/Vulkan/VulkanRenderPass.h"
#include "Platform/Vulkan/VulkanFramebuffers.h"
#include "Platform/Vulkan/VulkanDescriptorPool.h"
#include "Platform/Vulkan/VulkanCommandBuffer.h"

namespace Ballistic {

	class Renderer {
	public:
		Renderer() = default;
		~Renderer();

		void Init(std::shared_ptr<GLFWWindow> window);
		void Shutdown();

		VulkanInstance& getVulkanInstance() { return *m_Instance; }
		VulkanPhysicalDevice& getVulkanPhysicalDevice() { return *m_PhysicalDevice; }
		VulkanDevice& getVulkanDevice() { return *m_LogicalDevice; }
		VulkanSwapchain& getVulkanSwapchain() { return *m_Swapchain; }
		VulkanRenderPass& getVulkanRenderPass() { return *m_RenderPass; }
		VulkanFramebuffers& getVulkanFramebuffers() { return *m_Framebuffers; }
		VulkanDescriptorPool& getVulkanDescriptorPool() { return *m_DescriptorPool; }
		VulkanCommandBuffer& getVulkanCommandBuffer() { return *m_CommandBuffer; }

	private:
		std::unique_ptr<VulkanInstance> m_Instance;
		std::unique_ptr<VulkanPhysicalDevice> m_PhysicalDevice;
		std::unique_ptr<VulkanDevice> m_LogicalDevice;
		std::unique_ptr<VulkanSwapchain> m_Swapchain;
		std::unique_ptr<VulkanRenderPass> m_RenderPass;
		std::unique_ptr<VulkanFramebuffers> m_Framebuffers;
		std::unique_ptr<VulkanDescriptorPool> m_DescriptorPool;

    	std::unique_ptr<VulkanCommandBuffer> m_CommandBuffer;
	};
}