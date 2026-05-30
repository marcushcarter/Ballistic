#pragma once
#include "pch.h"

struct RenderGraph;

struct Pass
{
    const char* name = "Pass";
    virtual ~Pass() = default;
    virtual void Setup(RenderGraph& graph) = 0;
    virtual void Execute(VkCommandBuffer cmd, RenderGraph& graph) = 0;
};
