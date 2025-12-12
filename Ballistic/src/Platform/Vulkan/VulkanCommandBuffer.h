#pragma once

#include "bepch.h"

namespace Ballistic {

	class VulkanDevice;

	class VulkanCommandBuffer {
	public:
	    VulkanCommandBuffer(VulkanDevice& device);
	    ~VulkanCommandBuffer() = default;

	    VkCommandBuffer beginSingleTimeCommands();

	    void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkQueue queue);

    private:
    	VulkanDevice& m_Device;
	    VkCommandPool m_CommandPool = VK_NULL_HANDLE;

	    void destroyCommandPool();
	};
}