#pragma once
#include <core/dev_tools/renderbuffer_xray.h>
#include <core/dev_tools/debug_console.h>
#include <core/log/error.h>

namespace ballistic {

struct Renderer;
namespace drivers { struct RenderingDeviceDriverVulkan; }

struct DevSystems
{
    RenderBufferXray renderbuffer_xray;
    DebugConsole debug_console;

    Renderer* renderer = nullptr;
    drivers::RenderingDeviceDriverVulkan* device_driver = nullptr;

    Error create(Renderer* r_renderer, drivers::RenderingDeviceDriverVulkan* r_device_driver);
    void new_frame(float p_dt);
};

}