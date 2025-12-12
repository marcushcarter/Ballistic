#pragma once

#include "bepch.h"

namespace Ballistic {

	class VulkanInstance {
	public:
		struct Config {
	        bool enableValidation = false;
	        bool useGlfwExtensions = true;
	        const char* appName = "Ballistic Engine";
	        uint32_t appVersion = VK_MAKE_VERSION(1,0,0);
	        const char* engineName = "Ballistic Engine";
	        uint32_t engineVersion = VK_MAKE_VERSION(1,0,0);
	        uint32_t apiVersion = VK_API_VERSION_1_3;

	        std::vector<const char*> extraExtensions;

	        VkAllocationCallbacks* allocator = nullptr;
	    };

	    VulkanInstance(const Config& cfg = {});
	    ~VulkanInstance();

	    VkInstance get() const { return instance; }
	    VkAllocationCallbacks* getAllocator() const { return config.allocator; }

    private:
    	VkInstance instance = VK_NULL_HANDLE;
	    VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
	    Config config;
	};
}