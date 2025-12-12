#include "VulkanDescriptorPool.h"

#include "VulkanDevice.h"

namespace Ballistic {

	VulkanDescriptorPool::VulkanDescriptorPool(VulkanDevice& device, uint32_t maxSets)
		: m_Device(device) {
		
		VkDescriptorPoolSize poolSizes[] = {
            { VK_DESCRIPTOR_TYPE_SAMPLER, maxSets },
            { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, maxSets },
            { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, maxSets },
            { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, maxSets },
            { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, maxSets },
            { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, maxSets },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, maxSets },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, maxSets },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, maxSets },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, maxSets },
            { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, maxSets }
        };

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        poolInfo.maxSets = maxSets * std::size(poolSizes);
        poolInfo.poolSizeCount = static_cast<uint32_t>(std::size(poolSizes));
        poolInfo.pPoolSizes = poolSizes;

        if (vkCreateDescriptorPool(m_Device.get(), &poolInfo, nullptr, &m_DescriptorPool) != VK_SUCCESS)
            throw std::runtime_error("Failed to create descriptor pool");
	}

	VulkanDescriptorPool::~VulkanDescriptorPool() {
        if (m_DescriptorPool != VK_NULL_HANDLE) {
            vkDestroyDescriptorPool(m_Device.get(), m_DescriptorPool, nullptr);
            m_DescriptorPool = VK_NULL_HANDLE;
        }		
	}

}