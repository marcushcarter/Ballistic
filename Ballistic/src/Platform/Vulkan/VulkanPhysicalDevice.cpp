#include "VulkanPhysicalDevice.h"

#include "VulkanInstance.h"

namespace Ballistic {

	VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanInstance& instance, const Config& cfg)
		: vulkanInstance(instance), config(cfg) {

        VkInstance vkInstance = instance.get();
        
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr);
        if (deviceCount == 0)
            throw std::runtime_error("Failed to find GPUs with Vulkan support");

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(vkInstance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            VkPhysicalDeviceProperties props;
            vkGetPhysicalDeviceProperties(device, &props);

            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
            std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

            bool graphicsFound = !config.requireGraphics;
            bool computeFound  = !config.requireCompute;

            for (const auto& qf : queueFamilies) {
                if (config.requireGraphics && (qf.queueFlags & VK_QUEUE_GRAPHICS_BIT)) graphicsFound = true;
                if (config.requireCompute && (qf.queueFlags & VK_QUEUE_COMPUTE_BIT)) computeFound = true;
            }

            if (!graphicsFound || !computeFound) continue;

            if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU || physicalDevice == VK_NULL_HANDLE) {
                physicalDevice = device;
                if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE)
            throw std::runtime_error("Failed to find a suitable Vulkan GPU");
	}

}