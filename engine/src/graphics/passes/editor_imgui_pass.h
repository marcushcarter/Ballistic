#pragma once
#include "pch.h"
#include "graphics/render_graph/pass.h"
#include "graphics/render_graph/render_graph.h"

struct ImGuiLayer;

struct EditorImGuiPass : Pass
{
    ImGuiLayer* imguiLayer = nullptr;
    ResourceHandle finalIn;
    ResourceHandle swapOut;

    explicit EditorImGuiPass(ImGuiLayer& i) : imguiLayer(&i) { name = "EditorImGui"; }

    void Setup(RenderGraph& g) override;
    void Execute(VkCommandBuffer cmd, RenderGraph& g) override;
};
