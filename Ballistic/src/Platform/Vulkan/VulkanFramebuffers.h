#pragma once

#include "bepch.h"

namespace Ballistic {

	class VulkanDevice;
	class VulkanSwapchain;
	class VulkanRenderPass;

	class VulkanFramebuffers {
	public:
	    VulkanFramebuffers(VulkanDevice& device, VulkanSwapchain& swapchain, VulkanRenderPass& renderPass);
	    ~VulkanFramebuffers();

	    const std::vector<VkFramebuffer>& get() const { return framebuffers; }

    private:
    	VulkanDevice& device;
	    VulkanSwapchain& swapchain;
	    VulkanRenderPass& renderPass;

	    std::vector<VkFramebuffer> framebuffers;
	};
}