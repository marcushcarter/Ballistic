#pragma once
#include "pch.h"
#include "pass.h"
#include "graphics/vk/image/image_2d.h"

struct Image2D;
struct Pass;

struct ResourceHandle {
    uint32_t index = UINT32_MAX;
    bool IsValid() const { return index != UINT32_MAX; }
};

struct TransientImageDesc
{
    VkFormat format = VK_FORMAT_R8G8B8A8_UNORM;
    VkImageUsageFlags usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    VkImageAspectFlags aspect = VK_IMAGE_ASPECT_COLOR_BIT;

    enum class Sizing { ViewportRelative, Fixed };
    Sizing sizing = Sizing::ViewportRelative;
    float widthScale = 1.0f, heightScale = 1.0f;
    uint32_t fixedWidth = 0, fixedHeight = 0;
};

struct RenderGraph
{
    struct Resource {
        std::string name;
        Image2D* externalImage = nullptr;
        int32_t transientIndex = -1;

        VkImageLayout currentLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        VkPipelineStageFlags currentStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        VkAccessFlags currentAccess = 0;
    };

    struct Use {
        ResourceHandle handle;
        VkImageLayout layout;
        VkPipelineStageFlags stage;
        VkAccessFlags access;
        bool isWrite;
    };

    struct Node {
        std::unique_ptr<Pass> pass;
        std::vector<Use> uses;
    };

    struct Barrier {
        ResourceHandle handle;
        VkImageLayout oldLayout, newLayout;
        VkPipelineStageFlags srcStage, dstStage;
        VkAccessFlags srcAccess, dstAccess;
    };
    
    struct Step {
        std::vector<Barrier> barriers;
        Pass* pass;
    };

    struct TransientEntry
    {
        std::string name;
        Image2D image;
        TransientImageDesc desc;
        VkExtent2D currentExtent = {};
    };

    std::vector<Resource> resources;
    std::unordered_map<std::string, uint32_t> nameMap;
    std::vector<Node> nodes;
    std::vector<Step> plan;
    Node* currentSetup = nullptr;

    std::vector<std::unique_ptr<TransientEntry>> transientPool;
    VkExtent2D viewportExtent = {};

    VkDevice device = VK_NULL_HANDLE;
    const VkPhysicalDeviceMemoryProperties* memoryProps = nullptr;

    void Start(VkDevice device, const VkPhysicalDeviceMemoryProperties& memProps);
    void Shutdown();

    void SetViewport(VkExtent2D extent);

    void Reset();
    
    ResourceHandle Import(const char* name, Image2D* image);
    ResourceHandle Create(const char* name, const TransientImageDesc& desc, VkImageLayout layout, VkPipelineStageFlags stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VkAccessFlags access = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT);

    ResourceHandle Read(const char* name, VkImageLayout layout, VkPipelineStageFlags stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, VkAccessFlags access = VK_ACCESS_SHADER_READ_BIT);
    ResourceHandle Write(const char* name, VkImageLayout layout, VkPipelineStageFlags stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VkAccessFlags access = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT);
    
    void AddPass(std::unique_ptr<Pass> pass);
    
    void Compile();
    void Execute(VkCommandBuffer cmd);
    
    Image2D* GetImage(ResourceHandle handle);
};
