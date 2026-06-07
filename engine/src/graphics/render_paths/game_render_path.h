#pragma once
#include <graphics/render_graph/render_path.h>
#include <graphics/render_graph/render_graph.h>
#include <graphics/renderer.h>

#include <graphics/passes/scene_passes.h>
#include <graphics/passes/blit_pass.h>

struct GameRenderPath : RenderPath
{
    Renderer* renderer = nullptr;
    
    ScenePasses scenePasses;
    SwapchainBlitPass blitPass;

    explicit GameRenderPath(Renderer& r) : renderer(&r) {}

    bool CreateResources(Renderer& r) override {
        scenePasses.CreateResources(r);
        blitPass.CreateResources(r);
        return true;
    }

    void DestroyResources() override {
        scenePasses.DestroyResources();
        blitPass.DestroyResources();
    }
    
    void Build(RenderGraph& g, FrameGraph& fg) override {
        scenePasses.Build(g, fg);
        blitPass.AddPass(g, fg);
    }
};
