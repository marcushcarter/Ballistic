#pragma once
#include <vk/vk.h>
struct Renderer;
struct RenderGraph;
struct FrameGraph;

struct HBAOBlurPass
{
    Renderer* renderer = nullptr;

    bool CreateResources(Renderer& r);
    void DestroyResources();
    void AddPass(RenderGraph& g, FrameGraph& fg);
};
