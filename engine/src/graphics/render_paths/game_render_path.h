#pragma once
#include <graphics/render_graph/render_path.h>
#include <graphics/renderer.h>
#include <graphics/render_graph/render_graph.h>
#include <graphics/passes/placeholder_pass.h>
#include <graphics/passes/blit_pass.h>

struct Renderer;

struct GameRenderPath : RenderPath
{
    Renderer* renderer = nullptr;
    PlaceholderPass placeholderPass;
    SwapchainBlitPass blitPass;

    explicit GameRenderPath(Renderer& r) : renderer(&r) {}

    bool CreateResources(Renderer& r) override {
        placeholderPass.CreateResources(r);
        blitPass.CreateResources(r);
        return true;
    }

    void DestroyResources() override {
        placeholderPass.DestroyResources();
        blitPass.DestroyResources();
    }
    
    void Build(RenderGraph& g, FrameGraph& fg) override {
        placeholderPass.AddPass(g, fg);
        blitPass.AddPass(g, fg);
    }
};
