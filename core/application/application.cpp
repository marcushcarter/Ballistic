#include <core/application/application.h>
#include <core/error/error_macros.h>
#include <core/version.h>
#include <windows.h>
#include <chrono>
#include <iostream>

namespace ballistic {

Error Application::create(const ApplicationCreateInfo& p_info)
{
    using enum Error;
    Error err;

    std::cout << BALLISTIC_VERSION_NAME << " v" << BALLISTIC_VERSION_NUMBER << ".stable.official - https://ballisticgames.ca\n";
    
    create_info = p_info;

    err = window.create(p_info.window_title, p_info.width, p_info.height);
    BALLISTIC_ERR_FAIL_COND_V(err != Ok, err);

    err = vulkan_context.initialize();
    BALLISTIC_ERR_FAIL_COND_V(err != Ok, err);

    // can be called for other backends
    err = vulkan_context.surface_create(window.hwnd);
    BALLISTIC_ERR_FAIL_COND_V(err != Ok, err);

    // can be manually selected
    err = vulkan_context.physical_device_select();
    BALLISTIC_ERR_FAIL_COND_V(err != Ok, err);

    vulkan_device.context_driver = &vulkan_context;
    err = vulkan_device.initialize(vulkan_context.optimal_device_index, 1);
    BALLISTIC_ERR_FAIL_COND_V(err != Ok, err);

    renderer.device_driver = &vulkan_device;
    err = renderer.create(3);
    BALLISTIC_ERR_FAIL_COND_V(err != Ok, err);

    drivers::ImGuiDriverCreateInfo imgui_ci{};
    imgui_ci.hwnd = window.hwnd;
    imgui_ci.instance = vulkan_context.instance;
    imgui_ci.physical_device = vulkan_device.physical_device;
    imgui_ci.device = vulkan_device.device;
    imgui_ci.queue_family = vulkan_context.graphics_queue_family;
    imgui_ci.queue = vulkan_device.queue_families[vulkan_context.graphics_queue_family][0].queue;
    imgui_ci.color_format = renderer.swapchain.format;
    imgui_ci.image_count = 3;

    err = imgui.create(imgui_ci);
    BALLISTIC_ERR_FAIL_COND_V(err != Ok, err);

    return Ok;
}

void Application::destroy()
{
    vulkan_device.device_wait_idle();

    imgui.destroy();
    renderer.destroy();
    vulkan_device.shutdown();
    vulkan_context.shutdown();
    window.destroy();
}

int Application::run()
{
    using enum Error;
    Error err;

    err = on_init();
    BALLISTIC_ERR_FAIL_COND_V(err != Ok, static_cast<int>(err));

    auto lastTime = std::chrono::steady_clock::now();

    while (!window.should_close()) {
        auto now = std::chrono::steady_clock::now();
        double delta = std::chrono::duration<double>(now - lastTime).count();
        lastTime = now;

        window.poll_events();
        
        if (window.resize_requested) {
            if (window.pending_width != vulkan_context.surface.width || window.pending_height != vulkan_context.surface.height) {
                vulkan_context.surface_set_size(window.pending_width, window.pending_height);
            }
            window.resize_requested = false;
        }

        err = renderer.check_resize();
        BALLISTIC_ERR_FAIL_COND_V(err != Ok, static_cast<int>(err));
        
        imgui.new_frame();
        on_update((float)delta);
        imgui.render();

        renderer.begin_frame();

        VkRenderingAttachmentInfo color_attachment{ VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO };
        color_attachment.imageView = renderer.swapchain.image_views[renderer.swapchain.image_index];
        color_attachment.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        color_attachment.clearValue.color = { { 0.0f, 0.0f, 0.0f, 1.0f } };

        VkRenderingInfo rendering_info{ VK_STRUCTURE_TYPE_RENDERING_INFO };
        rendering_info.renderArea = { { 0, 0 }, { vulkan_context.surface.width, vulkan_context.surface.height } };
        rendering_info.layerCount = 1;
        rendering_info.colorAttachmentCount = 1;
        rendering_info.pColorAttachments = &color_attachment;

        vkCmdBeginRendering(renderer.cmd, &rendering_info);
        imgui.record_commands(renderer.cmd);
        vkCmdEndRendering(renderer.cmd);

        renderer.end_frame();
    }

    on_shutdown();
    destroy();
    return 0;
}

}