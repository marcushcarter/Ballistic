#pragma once

#include "bepch.h"

namespace Ballistic {

	class VulkanDevice;
	class VulkanSwapchain;

	class VulkanRenderPass {
	public:
		struct Config {
	        bool clearColor = true;
	    };

	    VulkanRenderPass(VulkanDevice& device, VulkanSwapchain& swapchain, const Config& cfg = {});
	    ~VulkanRenderPass();

	    VkRenderPass get() const { return renderPass; }

    private:
    	VulkanDevice& device;
	    VulkanSwapchain& swapchain;
	    Config config;

	    VkRenderPass renderPass = VK_NULL_HANDLE;
	};
}