#pragma once
#include "pch.h"
#include "graphics/render_graph/pass.h"
#include "graphics/render_graph/render_graph.h"

struct Renderer;

struct BlitToSwapchainPass : Pass
{
    Renderer* renderer = nullptr;
    ResourceHandle finalIn;
    ResourceHandle swapOut;

    explicit BlitToSwapchainPass(Renderer& r) : renderer(&r) { name = "BlitToSwapchain"; }

    void Setup(RenderGraph& g) override;
    void Execute(VkCommandBuffer cmd, RenderGraph& g) override;
};
