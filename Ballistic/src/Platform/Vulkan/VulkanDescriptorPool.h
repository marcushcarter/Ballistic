#pragma once

#include "bepch.h"

namespace Ballistic {

	class VulkanDevice;

	class VulkanDescriptorPool {
	public:
	    VulkanDescriptorPool(VulkanDevice& device, uint32_t maxSets = 1000);
	    ~VulkanDescriptorPool();

	    VkDescriptorPool get() const { return m_DescriptorPool; }

    private:
    	VulkanDevice& m_Device;
    	VkDescriptorPool m_DescriptorPool = VK_NULL_HANDLE;
	};
}