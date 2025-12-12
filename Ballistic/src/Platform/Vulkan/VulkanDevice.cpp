#include "VulkanDevice.h"

#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"

namespace Ballistic {

    VulkanDevice::VulkanDevice(VulkanPhysicalDevice& physicalDevice, const Config& cfg)
        : physicalDevice(physicalDevice), config(cfg) {

        // ===== Pick Queue Families =====

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice.get(), &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice.get(), &queueFamilyCount, queueFamilies.data());

        for (uint32_t i = 0; i < queueFamilies.size(); ++i) {
            const auto& qf = queueFamilies[i];
            if (config.enableGraphicsQueue && (qf.queueFlags & VK_QUEUE_GRAPHICS_BIT) && graphicsQueueFamily == UINT32_MAX)
                graphicsQueueFamily = i;

            if (config.enableComputeQueue && (qf.queueFlags & VK_QUEUE_COMPUTE_BIT) && computeQueueFamily == UINT32_MAX)
                computeQueueFamily = i;

            if (config.enableTransferQueue && (qf.queueFlags & VK_QUEUE_TRANSFER_BIT) && transferQueueFamily == UINT32_MAX)
                transferQueueFamily = i;
        }

        if (graphicsQueueFamily == UINT32_MAX)
            throw std::runtime_error("Failed to find a graphics queue family!");

        if (computeQueueFamily == UINT32_MAX) computeQueueFamily = graphicsQueueFamily;
        if (transferQueueFamily == UINT32_MAX) transferQueueFamily = graphicsQueueFamily;

        // ===== Create Logical Device =====

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueFamilies = { graphicsQueueFamily, computeQueueFamily, transferQueueFamily };
        float queuePriority = 1.0f;

        for (uint32_t family : uniqueFamilies) {
            VkDeviceQueueCreateInfo queueInfo{};
            queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueInfo.queueFamilyIndex = family;
            queueInfo.queueCount = 1;
            queueInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueInfo);
        }

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &config.enabledFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(config.extraExtensions.size());
        createInfo.ppEnabledExtensionNames = config.extraExtensions.data();

        if (vkCreateDevice(physicalDevice.get(), &createInfo, nullptr, &device) != VK_SUCCESS)
            throw std::runtime_error("Failed to create Vulkan logical device");

        vkGetDeviceQueue(device, graphicsQueueFamily, 0, &graphicsQueue);
        vkGetDeviceQueue(device, computeQueueFamily, 0, &computeQueue);
        vkGetDeviceQueue(device, transferQueueFamily, 0, &transferQueue);
    }

    VulkanDevice::~VulkanDevice() {
        if (device != VK_NULL_HANDLE) {
            vkDeviceWaitIdle(device);
            vkDestroyDevice(device, nullptr);
        }
    }

}