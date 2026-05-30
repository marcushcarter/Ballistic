#pragma once
#include "pch.h"
#include "graphics/render_graph/pass.h"
#include "graphics/render_graph/render_graph.h"

struct Renderer;
struct SplashRenderer;

struct SplashPass : Pass
{
    Renderer* renderer = nullptr;
    SplashRenderer* splash = nullptr;
    ResourceHandle swapOut;

    SplashPass(Renderer& r, SplashRenderer& s) : renderer(&r), splash(&s) { name = "Splash"; }

    void Setup(RenderGraph& g) override;
    void Execute(VkCommandBuffer cmd, RenderGraph& g) override;
};
