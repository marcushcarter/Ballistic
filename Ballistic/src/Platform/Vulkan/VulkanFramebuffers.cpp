#include "VulkanFramebuffers.h"

#include "VulkanDevice.h"
#include "VulkanSwapchain.h"
#include "VulkanRenderPass.h"

namespace Ballistic {

    VulkanFramebuffers::VulkanFramebuffers(VulkanDevice& device, VulkanSwapchain& swapchain, VulkanRenderPass& renderPass)
        : device(device), swapchain(swapchain), renderPass(renderPass) {

        const auto& swapImages = swapchain.getImages();
        const auto& swapViews = swapchain.getImageViews();
        framebuffers.resize(swapImages.size());

        for (size_t i = 0; i < swapImages.size(); ++i) {
            VkImageView attachments[] = { swapViews[i] };

            VkFramebufferCreateInfo fbInfo{};
            fbInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            fbInfo.renderPass = renderPass.get();
            fbInfo.attachmentCount = 1;
            fbInfo.pAttachments = attachments;
            fbInfo.width = swapchain.getExtent().width;
            fbInfo.height = swapchain.getExtent().height;
            fbInfo.layers = 1;

            if (vkCreateFramebuffer(device.get(), &fbInfo, nullptr, &framebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create framebuffer");
            }
        }
    }

    VulkanFramebuffers::~VulkanFramebuffers() {
        for (auto fb : framebuffers) {
            vkDestroyFramebuffer(device.get(), fb, nullptr);
        }        
    }

}