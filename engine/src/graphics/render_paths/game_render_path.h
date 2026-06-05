#pragma once
#include <graphics/render_graph/render_path.h>

struct Renderer;

struct GameRenderPath : RenderPath
{
    Renderer* renderer = nullptr;
    explicit GameRenderPath(Renderer& r) : renderer(&r) {}
    void Build(RenderGraph& g) override;
};
