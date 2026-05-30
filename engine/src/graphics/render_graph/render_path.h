#pragma once
#include "pch.h"

struct RenderGraph;

struct RenderPath
{
    virtual ~RenderPath() = default;
    virtual void Build(RenderGraph& graph) = 0;
};
