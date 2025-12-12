#pragma once

#include "bepch.h"

namespace Ballistic {

	class VulkanPhysicalDevice;
	class VulkanDevice;

	class VulkanSwapchain {
	public:
		struct Config {
	        VkSurfaceKHR surface = VK_NULL_HANDLE;
	        uint32_t imageCount = 2;
	        VkFormat imageFormat = VK_FORMAT_B8G8R8A8_SRGB;
	        VkColorSpaceKHR colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	        VkExtent2D extent{};
	        VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
	        bool enableVSync = true;
	    };

	    VulkanSwapchain(VulkanDevice& device, VulkanPhysicalDevice& physicalDevice, const Config& cfg = {});
	    ~VulkanSwapchain();

	    VkSwapchainKHR get() const { return swapchain; }

	    VkFormat getFormat() const { return config.imageFormat; }
	    VkExtent2D getExtent() const { return config.extent; }
	    const std::vector<VkImage>& getImages() const { return images; }
	    const std::vector<VkImageView>& getImageViews() const { return imageViews; }

    private:
	    VulkanDevice& device;
	    VulkanPhysicalDevice& physicalDevice;
	    Config config;

	    VkSwapchainKHR swapchain = VK_NULL_HANDLE;
	    std::vector<VkImage> images;
	    std::vector<VkImageView> imageViews;
	};
}