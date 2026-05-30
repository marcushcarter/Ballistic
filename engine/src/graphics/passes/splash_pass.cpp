#include "splash_pass.h"
#include "graphics/renderer.h"
#include "graphics/splash_renderer.h"
#include "graphics/vk/image/image_2d.h"

void SplashPass::Setup(RenderGraph& g)
{
    swapOut = g.Write("swapchain", VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT);
}

void SplashPass::Execute(VkCommandBuffer cmd, RenderGraph& g)
{
    Image2D* swap = g.GetImage(swapOut);
    if (!swap || !splash || !renderer) return;

    VkRenderingAttachmentInfo color{};
    color.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
    color.imageView = swap->GetView();
    color.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    color.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    color.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    color.clearValue.color = { 0.2f, 0.4f, 0.8f, 1.0f };

    VkRenderingInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;
    info.renderArea = { {0,0}, swap->extent };
    info.layerCount = 1;
    info.colorAttachmentCount = 1;
    info.pColorAttachments = &color;

    vkCmdBeginRendering(cmd, &info);
    splash->RecordSplashContent(cmd, *renderer);
    vkCmdEndRendering(cmd);
}
