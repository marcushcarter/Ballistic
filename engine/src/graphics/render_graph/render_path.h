#pragma once
#include <graphics/render_graph/render_graph.h>

struct Renderer;
struct RenderGraph;

// struct GBufferOutput {
//     ResourceHandle albedo, normal, material, depth;
// };

// struct IndirectDrawData {
//     ResourceHandle commands;
//     ResourceHandle count;
//     ResourceHandle visibility;
//     ResourceHandle offsets;
//     ResourceHandle writtenCount;
// };

struct FrameGraph {
    // Imported
    ResourceHandle finalImage;
    ResourceHandle swapchain;
    ResourceHandle frameUniform;

    
    ResourceHandle deferredLightImage;
};

struct RenderPath
{
    virtual ~RenderPath() = default;
    virtual bool CreateResources(Renderer& r) = 0;
    virtual void DestroyResources() = 0;
    virtual void Build(RenderGraph& g, FrameGraph& fg) = 0;
};
