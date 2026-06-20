#include <core/application/application.h>
#include <windows.h>
#include <chrono>
#include <iostream>

namespace ballistic {

void Application::create(const ApplicationCreateInfo& p_info)
{
    // std::cout << "%s v%d.%d.%d.stable.official.%s - https://ballisticgames.ca", APP_NAME, APP_VERSION_MAJOR, APP_VERSION_MINOR, APP_VERSION_PATCH, APP_COMMIT);

    create_info = p_info;
    window.create(p_info.window_title, p_info.width, p_info.height);

    ImGuiLayerCreateInfo imgui_layer_create_info{};
    imgui_layer_create_info.hwnd = window.hwnd;

    // imgui_layer.create(imgui_layer_create_info);
}

void Application::destroy()
{
    // imgui_layer.destroy();
    window.destroy();
}

int Application::run()
{
    on_init();

    auto lastTime = std::chrono::steady_clock::now();
    auto startTime = lastTime;

    while (!window.should_close()) {
        auto now = std::chrono::steady_clock::now();
        double delta = std::chrono::duration<double>(now - lastTime).count();
        lastTime = now;

        window.poll_events();
        // imgui_layer.new_frame();

        on_update((float)delta);

        // imgui_layer.render();
    }

    on_shutdown();
    destroy();
    return 0;
}

}