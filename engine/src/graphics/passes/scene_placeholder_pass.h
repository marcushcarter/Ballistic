#pragma once
#include "pch.h"
#include "graphics/render_graph/pass.h"
#include "graphics/render_graph/render_graph.h"

struct ScenePlaceholderPass : Pass
{
    ResourceHandle finalOut;

    ScenePlaceholderPass() { name = "ScenePlaceholder"; }
    
    void Setup(RenderGraph& g) override;
    void Execute(VkCommandBuffer cmd, RenderGraph& g) override;
};
