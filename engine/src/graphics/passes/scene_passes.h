#pragma once
#include <graphics/passes/main_z_pass.h>
#include <graphics/passes/main_gbuffer_pass.h>
#include <graphics/passes/hbao_pass.h>
#include <graphics/passes/hbao_blur_pass.h>
#include <graphics/passes/light_pass.h>
#include <graphics/passes/placeholder_pass.h>

struct Renderer;
struct RenderGraph;
struct FrameGraph;

struct ScenePasses
{
    MainZPass mainZPass;
    MainGBufferPass mainGBufferPass;
    HBAOPass hbaoPass;
    HBAOBlurPass hbaoBlurPass;
    LightPass lightPass;
    PlaceholderPass placeholderPass;

    bool CreateResources(Renderer& r) {
        mainZPass.CreateResources(r);
        mainGBufferPass.CreateResources(r);
        hbaoPass.CreateResources(r);
        hbaoBlurPass.CreateResources(r);
        lightPass.CreateResources(r);
        placeholderPass.CreateResources(r);
        return true;
    }

    void DestroyResources() {
        mainZPass.DestroyResources();
        mainGBufferPass.DestroyResources();
        hbaoPass.DestroyResources();
        hbaoBlurPass.DestroyResources();
        lightPass.DestroyResources();
        placeholderPass.DestroyResources();
    }
    
    void Build(RenderGraph& g, FrameGraph& fg) {
        mainZPass.AddPass(g, fg);
        mainGBufferPass.AddPass(g, fg);

        // cascadedshadowmaps
        // spotlightshadowmaps

        hbaoPass.AddPass(g, fg);
        hbaoBlurPass.AddPass(g, fg);
        lightPass.AddPass(g, fg);
        
        // subsurfacescattering
        // skyandfog
        // haircoverage (depth testing)
        // maintransparentdepth
        // maintransparent
        // fgtransparent
        // finalpost
        // overlay
        // upsampling
        
        placeholderPass.AddPass(g, fg);
    }
};
