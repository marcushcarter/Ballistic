#include "VulkanSwapchain.h"

#include "VulkanPhysicalDevice.h"
#include "VulkanDevice.h"
#include "VulkanInstance.h"

namespace Ballistic {

    VkSurfaceFormatKHR chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
        for (const auto& format : availableFormats) {
            if (format.format == VK_FORMAT_B8G8R8A8_SRGB && 
                format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return format;
            }
        }
        return availableFormats[0];
    }

    VkPresentModeKHR choosePresentMode(const std::vector<VkPresentModeKHR>& modes, bool enableVSync) {
        if (enableVSync) return VK_PRESENT_MODE_FIFO_KHR;
        for (const auto& mode : modes) {
            if (mode == VK_PRESENT_MODE_MAILBOX_KHR) return mode;
        }
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D chooseExtent(const VkSurfaceCapabilitiesKHR& caps, VkExtent2D defaultExtent) {
        if (caps.currentExtent.width != UINT32_MAX) return caps.currentExtent;

        auto clamp = [](uint32_t val, uint32_t minVal, uint32_t maxVal) {
            return std::max(minVal, std::min(maxVal, val));
        };

        VkExtent2D actualExtent = defaultExtent;
        actualExtent.width = clamp(actualExtent.width, caps.minImageExtent.width, caps.maxImageExtent.width);
        actualExtent.height = clamp(actualExtent.height, caps.minImageExtent.height, caps.maxImageExtent.height);
        return actualExtent;
    }

    VulkanSwapchain::VulkanSwapchain(VulkanDevice& dev, VulkanPhysicalDevice& phys, const Config& cfg)
        : device(dev), physicalDevice(phys), config(cfg) {

        // ===== Create Swapchain =====

        VkSurfaceCapabilitiesKHR capabilities;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice.get(), config.surface, &capabilities);

        uint32_t formatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.get(), config.surface, &formatCount, nullptr);
        std::vector<VkSurfaceFormatKHR> formats(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.get(), config.surface, &formatCount, formats.data());

        uint32_t presentModeCount = 0;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.get(), config.surface, &presentModeCount, nullptr);
        std::vector<VkPresentModeKHR> presentModes(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.get(), config.surface, &presentModeCount, presentModes.data());

        VkSurfaceFormatKHR surfaceFormat = chooseSurfaceFormat(formats);
        VkPresentModeKHR presentMode = choosePresentMode(presentModes, config.enableVSync);
        VkExtent2D extent = chooseExtent(capabilities, config.extent);

        config.imageFormat = surfaceFormat.format;
        config.colorSpace = surfaceFormat.colorSpace;
        config.extent = extent;

        VkSwapchainCreateInfoKHR swapchainInfo{};
        swapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainInfo.surface = config.surface;
        swapchainInfo.minImageCount = config.imageCount;
        swapchainInfo.imageFormat = surfaceFormat.format;
        swapchainInfo.imageColorSpace = surfaceFormat.colorSpace;
        swapchainInfo.imageExtent = extent;
        swapchainInfo.imageArrayLayers = 1;
        swapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        uint32_t queueFamily = device.getGraphicsQueueFamily();
        swapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainInfo.queueFamilyIndexCount = 0;
        swapchainInfo.pQueueFamilyIndices = nullptr;

        swapchainInfo.preTransform = capabilities.currentTransform;
        swapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainInfo.presentMode = presentMode;
        swapchainInfo.clipped = VK_TRUE;
        swapchainInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(device.get(), &swapchainInfo, nullptr, &swapchain) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create Vulkan swapchain");
        }

        uint32_t imageCount = 0;
        vkGetSwapchainImagesKHR(device.get(), swapchain, &imageCount, nullptr);
        images.resize(imageCount);
        vkGetSwapchainImagesKHR(device.get(), swapchain, &imageCount, images.data());

        // ===== Create Image Views =====

        imageViews.resize(images.size());

        for (size_t i = 0; i < images.size(); ++i) {
            VkImageViewCreateInfo viewInfo{};
            viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewInfo.image = images[i];
            viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            viewInfo.format = config.imageFormat;
            viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            viewInfo.subresourceRange.baseMipLevel = 0;
            viewInfo.subresourceRange.levelCount = 1;
            viewInfo.subresourceRange.baseArrayLayer = 0;
            viewInfo.subresourceRange.layerCount = 1;

            if (vkCreateImageView(device.get(), &viewInfo, nullptr, &imageViews[i]) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create swapchain image view");
            }
        }
    }

    VulkanSwapchain::~VulkanSwapchain() {
        for (auto view : imageViews) {
            vkDestroyImageView(device.get(), view, nullptr);
        }
        if (swapchain != VK_NULL_HANDLE) {
            vkDestroySwapchainKHR(device.get(), swapchain, nullptr);
        }
    }

}