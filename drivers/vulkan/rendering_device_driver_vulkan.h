#pragma once

#include <drivers/vulkan/rendering_context_driver_vulkan.h>

#include <shaderc/shaderc.hpp>
#include <vk_mem_alloc.h>

#include <drivers/vulkan/ballistic_vulkan.h>

namespace ballistic::drivers {

struct RenderingDeviceDriverVulkan
{
    /***************/
    /**** SETUP ****/
    /***************/
	
    struct Queue {
		VkQueue queue = VK_NULL_HANDLE;
	};

    struct SubgroupCapabilities {
        uint32_t size = 0;
        VkShaderStageFlags supported_stages = 0;
        VkSubgroupFeatureFlags supported_operations = 0;
    };

    VkDevice device = VK_NULL_HANDLE;
    RenderingContextDriverVulkan* context_driver = nullptr;
    uint32_t device_index = 0;
    DriverDevice driver_device;
    VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    uint32_t frame_count = 1;
	VkPhysicalDeviceProperties physical_device_properties = {};
	VkPhysicalDeviceFeatures physical_device_features = {};
	VkPhysicalDeviceFeatures requested_device_features = {};
    std::unordered_map<std::string, bool> requested_device_extensions;
    std::unordered_set<std::string> enabled_device_extension_names;
    std::vector<std::vector<Queue>> queue_families;
    SubgroupCapabilities subgroup_capabilities;

	void _register_requested_device_extension(const std::string& p_extension_name, bool p_required);
    Error _initialize_device_extensions();
    void _get_device_properties();
    Error _check_device_features();
    Error _check_device_capabilities();
    Error _add_queue_create_info(std::vector<VkDeviceQueueCreateInfo> &r_queue_create_info);
    Error _initialize_device(const std::vector<VkDeviceQueueCreateInfo> &p_queue_create_info);
    Error _initialize_allocator();
    Error _initialize_pipeline_cache();

    void _check_subgroup_capabilities();

    Error initialize(uint32_t p_device_index, uint32_t p_frame_count);
    void shutdown();

    Error device_wait_idle();

    /****************/
    /**** MEMORY ****/
    /****************/

    VmaAllocator allocator = nullptr;

    /****************/
    /**** FENCES ****/
    /****************/

    VkFence fence_create(bool p_signaled = true);
    void fence_free(VkFence& r_fence);
    Error fence_wait(VkFence p_fence, uint64_t p_timeout = UINT64_MAX);
    Error fence_reset(VkFence p_fence);

    /********************/
    /**** SEMAPHORES ****/
    /********************/

    VkSemaphore semaphore_create();
    void semaphore_free(VkSemaphore& r_semaphore);

    /******************/
    /**** COMMANDS ****/
    /******************/
    
    // ----- POOL -----

    struct CommandPool {
        VkCommandPool command_pool = VK_NULL_HANDLE;
        VkCommandBufferLevel buffer_level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    };

    CommandPool command_pool_create(uint32_t p_queue_family_index, VkCommandBufferLevel p_buffer_level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);
    void command_pool_free(CommandPool& r_cmd_pool);
    Error command_pool_reset(CommandPool& r_cmd_pool);
    
    // ----- BUFFER -----

    VkCommandBuffer command_buffer_create(CommandPool& p_cmd_pool);
    Error command_buffer_begin(VkCommandBuffer p_cmd_buffer, VkCommandBufferUsageFlags p_flags = 0);
    Error command_buffer_end(VkCommandBuffer p_cmd_buffer);

    /*******************/
    /**** SWAPCHAIN ****/
    /*******************/

    struct Swapchain {
        VkSwapchainKHR swapchain = VK_NULL_HANDLE;
        RenderingContextDriverVulkan::Surface* surface = nullptr;
        VkFormat format = VK_FORMAT_UNDEFINED;
        VkColorSpaceKHR color_space = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        std::vector<VkImage> images;
        std::vector<VkImageView> image_views;
        std::vector<VkSemaphore> present_semaphores;
        uint32_t image_index = 0;
    };

    Swapchain swapchain;

    bool _determine_swapchain_format(RenderingContextDriverVulkan::Surface* r_surface, VkSurfaceFormatKHR &r_surface_format);
    void _swapchain_release();
    
    Error swapchain_create(RenderingContextDriverVulkan::Surface* r_surface);
    Error swapchain_resize(uint32_t p_desired_framebuffer_count);
    void swapchain_free();
    Error swapchain_acquire_next_image(VkSemaphore p_signal_semaphore);

    Error update_swapchain();

	/*********************/
	/**** DESCRIPTORS ****/
	/*********************/

    // ----- BINDLESS HEAP -----

    struct IndexAllocator {
        uint32_t cap = 0;
        uint32_t high_water = 0;
        std::vector<uint32_t> free_list;

        uint32_t acquire() {
            if (!free_list.empty()) { uint32_t i = free_list.back(); free_list.pop_back(); return i; }
            if (high_water < cap) return high_water++;
            return UINT32_MAX;
        }
        void release(uint32_t i) { free_list.push_back(i); }
    };

    struct BindlessHeap {
        VkDescriptorSet set = VK_NULL_HANDLE;
        VkDescriptorSetLayout layout = VK_NULL_HANDLE;
        VkDescriptorPool pool = VK_NULL_HANDLE;
        VkPipelineLayout pipeline_layout = VK_NULL_HANDLE;
        
        IndexAllocator sampled_alloc;
        IndexAllocator storage_alloc;

        static constexpr uint32_t BINDING_SAMPLED = 0;
        static constexpr uint32_t BINDING_STORAGE = 1;
        static constexpr uint32_t BINDING_SAMPLER = 2;
        static constexpr uint32_t PUSH_CONSTANT_SIZE = 128;
    };

    BindlessHeap bindless_heap;

    Error bindless_heap_create(uint32_t p_sampled_count = 16384, uint32_t p_storage_count = 4096, uint32_t p_samplers_count = 256);
    void bindless_heap_free();
    uint32_t bindless_heap_alloc_sampled(VkImageView p_image_view);
    uint32_t bindless_heap_alloc_storage(VkImageView p_image_view);
    void bindless_heap_free_sampled(uint32_t p_index);
    void bindless_heap_free_storage(uint32_t p_index);
    void bindless_heap_register_sampler(uint32_t p_index, VkSampler p_sampler);

	/*******************/
	/**** RENDERING ****/
	/*******************/

    // void command_render_set_viewport(VkCommandBuffer p_cmd_buffer, VectorView<Rect2i> p_viewports);
	// void command_render_set_scissor(VkCommandBuffer p_cmd_buffer, VectorView<Rect2i> p_scissors);

    // bind vertex buffers
    // bind index buffers

    // draw indirect
    // draw
    // draw indexed

    // bid render/compute pipeline
    // bind render/comput uniform sets


};

}