#pragma once
#include <graphics/render_graph/render_graph.h>

struct Renderer;
struct RenderGraph;

struct GBufferOutput { ResourceHandle albedo, normal; };

struct FrameGraph {
    // Imported
    ResourceHandle finalImage;
    ResourceHandle swapchain;
    ResourceHandle frameUniform;

    ResourceHandle mainZBuffer;
    GBufferOutput gbuffer;
    ResourceHandle aoRaw;
    ResourceHandle aoBlurred;
    ResourceHandle hdrLightImage;
};

struct RenderPath
{
    virtual ~RenderPath() = default;
    virtual bool CreateResources(Renderer& r) = 0;
    virtual void DestroyResources() = 0;
    virtual void Build(RenderGraph& g, FrameGraph& fg) = 0;
};
