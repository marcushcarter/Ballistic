#pragma once
#include "pch.h"
#include "graphics/render_graph/render_path.h"

struct Renderer;
struct SplashRenderer;

struct SplashRenderPath : RenderPath
{
    Renderer* renderer = nullptr;
    SplashRenderer* splash = nullptr;
    SplashRenderPath(Renderer& r, SplashRenderer& s) : renderer(&r), splash(&s) {}
    void Build(RenderGraph& g) override;
};
