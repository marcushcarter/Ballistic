#pragma once

#include "bepch.h"

namespace Ballistic {

	class VulkanInstance;

	class VulkanPhysicalDevice {
	public:
		struct Config {
	        bool requireGraphics = true;
	        bool requireCompute = false;
	        bool requirePresent = true;
	    };

	    VulkanPhysicalDevice(VulkanInstance& instance, const Config& cfg = {});
	    ~VulkanPhysicalDevice() = default;

	    VkPhysicalDevice get() const { return physicalDevice; }

    private:
    	VulkanInstance& vulkanInstance;
	    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	    Config config;
	};
}