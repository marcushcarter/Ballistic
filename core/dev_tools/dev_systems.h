#pragma once
#include <core/dev_tools/xray.h>
#include <core/error/error.h>

namespace ballistic {

struct Renderer;
namespace drivers { struct RenderingDeviceDriverVulkan; }

struct DevSystems
{
    Xray xray;

    Renderer* renderer = nullptr;
    drivers::RenderingDeviceDriverVulkan* device_driver = nullptr;

    Error create(Renderer* r_renderer, drivers::RenderingDeviceDriverVulkan* r_device_driver);
    void new_frame(float p_dt);
};

}