#pragma once

#include "bepch.h"

namespace Ballistic {

	class VulkanPhysicalDevice;

	class VulkanDevice {
	public:
		struct Config {
	        bool enableGraphicsQueue = true;
	        bool enableComputeQueue = false;
	        bool enableTransferQueue = false;
	        std::vector<const char*> extraExtensions;
	        VkPhysicalDeviceFeatures enabledFeatures{};
	    };

	    VulkanDevice(VulkanPhysicalDevice& physicalDevice, const Config& cfg = {});
	    ~VulkanDevice();

	    VkDevice get() const { return device; }

	    VkQueue getGraphicsQueue() const { return graphicsQueue; }
	    VkQueue getComputeQueue() const { return computeQueue; }
	    VkQueue getTransferQueue() const { return transferQueue; }

	    uint32_t getGraphicsQueueFamily() const { return graphicsQueueFamily; }
		uint32_t getComputeQueueFamily() const { return computeQueueFamily; }
		uint32_t getTransferQueueFamily() const { return transferQueueFamily; }

    private:
    	VulkanPhysicalDevice& physicalDevice;
	    Config config;

	    VkDevice device = VK_NULL_HANDLE;

	    uint32_t graphicsQueueFamily = UINT32_MAX;
	    uint32_t computeQueueFamily = UINT32_MAX;
	    uint32_t transferQueueFamily = UINT32_MAX;

	    VkQueue graphicsQueue = VK_NULL_HANDLE;
	    VkQueue computeQueue = VK_NULL_HANDLE;
	    VkQueue transferQueue = VK_NULL_HANDLE;
	};
}