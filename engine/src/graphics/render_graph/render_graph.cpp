#include "render_graph.h"
#include "pass.h"

void RenderGraph::Start(VkDevice dev, const VkPhysicalDeviceMemoryProperties& memProps)
{
    device = dev;
    memoryProps = &memProps;
}

void RenderGraph::Shutdown()
{
    for (auto& t : transientPool) t->image.Destroy();
    transientPool.clear();
}

void RenderGraph::SetViewport(VkExtent2D extent)
{
    viewportExtent = extent;
}

void RenderGraph::Reset()
{
    resources.clear();
    nameMap.clear();
    nodes.clear();
    plan.clear();
    currentSetup = nullptr;
}

ResourceHandle RenderGraph::Import(const char* name, Image2D* image)
{
    auto it = nameMap.find(name);
    if (it != nameMap.end()) {
        resources[it->second].externalImage = image;
        return { it->second };
    }
    Resource r{};
    r.name = name;
    r.externalImage = image;
    uint32_t idx = (uint32_t)resources.size();
    resources.push_back(std::move(r));
    nameMap[name] = idx;
    return { idx };
}

static VkExtent2D ComputeExtent(const TransientImageDesc& desc, VkExtent2D viewport)
{
    if (desc.sizing == TransientImageDesc::Sizing::Fixed) {
        return { desc.fixedWidth, desc.fixedHeight };
    }
    return {
        (uint32_t)(viewport.width * desc.widthScale),
        (uint32_t)(viewport.height * desc.heightScale)
    };
}

static int32_t AcquireTransient(RenderGraph& g, const char* name, const TransientImageDesc& desc)
{
    VkExtent2D target = ComputeExtent(desc, g.viewportExtent);
    if (target.width == 0 || target.height == 0) {
        LOG_ERROR("RenderGraph: transient '%s' has zero extent (viewport not set?)", name);
        return -1;
    }

    // find existing entry by name
    for (size_t i = 0; i < g.transientPool.size(); ++i) {
        if (g.transientPool[i]->name == name) {
            auto& e = *g.transientPool[i];
            if (e.currentExtent.width == target.width && e.currentExtent.height == target.height
                && e.desc.format == desc.format) {
                return (int32_t)i;
            }
            // size or format mismatch — recreate
            e.image.Destroy();
            Image2DDesc d{};
            d.extent = target;
            d.format = desc.format;
            d.usage = desc.usage;
            d.aspect = desc.aspect;
            d.debugName = name;
            if (!e.image.Create(g.device, *g.memoryProps, d)) {
                LOG_ERROR("RenderGraph: failed to recreate transient '%s'", name);
                return -1;
            }
            e.desc = desc;
            e.currentExtent = target;
            return (int32_t)i;
        }
    }

    // create new entry
    auto entry = std::make_unique<RenderGraph::TransientEntry>();
    entry->name = name;
    entry->desc = desc;
    entry->currentExtent = target;
    Image2DDesc d{};
    d.extent = target;
    d.format = desc.format;
    d.usage = desc.usage;
    d.aspect = desc.aspect;
    d.debugName = name;
    if (!entry->image.Create(g.device, *g.memoryProps, d)) {
        LOG_ERROR("RenderGraph: failed to create transient '%s'", name);
        return -1;
    }

    g.transientPool.push_back(std::move(entry));
    return (int32_t)g.transientPool.size() - 1;
}

ResourceHandle RenderGraph::Create(const char* name, const TransientImageDesc& desc, VkImageLayout layout, VkPipelineStageFlags stage, VkAccessFlags access)
{
    auto it = nameMap.find(name);
    if (it != nameMap.end()) {
        LOG_ERROR("RenderGraph: resource '%s' already declared this frame", name);
        return { it->second };
    }

    int32_t poolIdx = AcquireTransient(*this, name, desc);
    if (poolIdx < 0) return {};

    Resource r{};
    r.name = name;
    r.transientIndex = poolIdx;
    uint32_t idx = (uint32_t)resources.size();
    resources.push_back(std::move(r));
    nameMap[name] = idx;
    if (currentSetup) currentSetup->uses.push_back({ { idx }, layout, stage, access, true });
    return { idx };
}

static ResourceHandle Resolve(RenderGraph& g, const char* name)
{
    auto it = g.nameMap.find(name);
    if (it == g.nameMap.end()) {
        LOG_ERROR("RenderGraph: resource '%s' not found (must be Imported first)", name);
        return {};
    }
    return { it->second };
}

ResourceHandle RenderGraph::Read(const char* name, VkImageLayout layout, VkPipelineStageFlags stage, VkAccessFlags access)
{
    ResourceHandle h = Resolve(*this, name);
    if (currentSetup && h.IsValid())
        currentSetup->uses.push_back({ h, layout, stage, access, false });
    return h;
}

ResourceHandle RenderGraph::Write(const char* name, VkImageLayout layout, VkPipelineStageFlags stage, VkAccessFlags access)
{
    ResourceHandle h = Resolve(*this, name);
    if (currentSetup && h.IsValid())
        currentSetup->uses.push_back({ h, layout, stage, access, true });
    return h;
}

void RenderGraph::AddPass(std::unique_ptr<Pass> pass)
{
    nodes.emplace_back();
    nodes.back().pass = std::move(pass);
    currentSetup = &nodes.back();
    nodes.back().pass->Setup(*this);
    currentSetup = nullptr;
}

void RenderGraph::Compile()
{
    plan.clear();
    plan.reserve(nodes.size());

    for (auto& r : resources) {
        Image2D* img = (r.transientIndex >= 0) ? &transientPool[r.transientIndex]->image : r.externalImage;
        if (img) {
            r.currentLayout = img->layout;
            r.currentStage = img->stage ? img->stage : VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            r.currentAccess = img->access;
        }
    }
    
    for (auto& node : nodes) {
        Step step{};
        step.pass = node.pass.get();

        for (auto& use : node.uses) {
            Resource& res = resources[use.handle.index];
            if (res.currentLayout != use.layout) {
                Barrier b{};
                b.handle = use.handle;
                b.oldLayout = res.currentLayout;
                b.newLayout = use.layout;
                b.srcStage = res.currentStage ? res.currentStage : VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
                b.dstStage = use.stage;
                b.srcAccess = res.currentAccess;
                b.dstAccess = use.access;
                step.barriers.push_back(b);

                res.currentLayout = use.layout;
                res.currentStage = use.stage;
                res.currentAccess = use.access;
            }
        }

        plan.push_back(std::move(step));
    }
}

void RenderGraph::Execute(VkCommandBuffer cmd)
{
    for (auto& step : plan) {
        if (!step.barriers.empty()) {
            std::vector<VkImageMemoryBarrier2> barriers;
            barriers.reserve(step.barriers.size());

            for (auto& b : step.barriers) {
                Image2D* img = GetImage(b.handle);
                if (!img) continue;

                VkImageMemoryBarrier2 vb{};
                vb.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
                vb.srcStageMask = b.srcStage;
                vb.srcAccessMask = b.srcAccess;
                vb.dstStageMask = b.dstStage;
                vb.dstAccessMask = b.dstAccess;
                vb.oldLayout = b.oldLayout;
                vb.newLayout = b.newLayout;
                vb.image = img->GetImage();
                vb.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
                vb.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
                vb.subresourceRange.aspectMask = img->aspect;
                vb.subresourceRange.baseMipLevel = 0;
                vb.subresourceRange.levelCount = img->mipLevels;
                vb.subresourceRange.baseArrayLayer = 0;
                vb.subresourceRange.layerCount = img->layers;
                barriers.push_back(vb);

                img->layout = b.newLayout;
                img->stage  = b.dstStage;
                img->access = b.dstAccess;
            }

            if (!barriers.empty()) {
                VkDependencyInfo dep{};
                dep.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
                dep.imageMemoryBarrierCount = (uint32_t)barriers.size();
                dep.pImageMemoryBarriers = barriers.data();
                vkCmdPipelineBarrier2(cmd, &dep);
            }
        }

        step.pass->Execute(cmd, *this);
    }
}

Image2D* RenderGraph::GetImage(ResourceHandle handle)
{
    if (!handle.IsValid()) return nullptr;
    Resource& r = resources[handle.index];
    if (r.transientIndex >= 0) return &transientPool[r.transientIndex]->image;
    return r.externalImage;
}
