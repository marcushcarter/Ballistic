#include "VulkanInstance.h"

namespace Ballistic {

	VulkanInstance::VulkanInstance(const Config& cfg) : config(cfg)  {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = config.appName;
        appInfo.applicationVersion = config.appVersion;
        appInfo.pEngineName = config.engineName;
        appInfo.engineVersion = config.engineVersion;
        appInfo.apiVersion = config.apiVersion;

        std::vector<const char*> extensions = config.extraExtensions;
        if (config.useGlfwExtensions) {
            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
            extensions.insert(extensions.end(), glfwExtensions, glfwExtensions + glfwExtensionCount);
        }

        std::vector<const char*> layers;
        if (config.enableValidation) layers.push_back("VK_LAYER_KHRONOS_validation");

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();
        createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
        createInfo.ppEnabledLayerNames = layers.empty() ? nullptr : layers.data();

        if (vkCreateInstance(&createInfo, config.allocator, &instance) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create Vulkan instance!");
        }

        if (config.enableValidation) {
            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
            debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            
            debugCreateInfo.pfnUserCallback = [](VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* data, void* userData) -> VkBool32 {
                std::cerr << "Validation: " << data->pMessage << std::endl; return VK_FALSE;
            };

            auto func = (PFN_vkCreateDebugUtilsMessengerEXT)
                vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
            if (func != nullptr)
                func(instance, &debugCreateInfo, nullptr, &debugMessenger);
        }

	}

	VulkanInstance::~VulkanInstance() {
        if (debugMessenger != VK_NULL_HANDLE) {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)
                vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
            if (func) func(instance, debugMessenger, config.allocator);
        }

        if (instance != VK_NULL_HANDLE)
            vkDestroyInstance(instance, config.allocator);
    }

	
}